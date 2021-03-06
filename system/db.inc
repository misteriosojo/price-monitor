<?php
require_once(__DIR__ . '/../system/config.inc');

/**
 * Class DatabaseManager (Database).
 *
 * This class is the middleware with the Database:
 * - Create table (for the setup)
 * - Get product list
 *
 * @version 1.0
 * @author Misterioso <misterioso@crypted2.com>
 */
class DatabaseManager
{
    // Ip + Port + AuthData + DatabaseStructure
    private $ipDB, $portDB;
    private $userDB, $passwordDB;
    private $dbName, $tableProducts, $tableCrawler;
    private $timeoutDB;

    // Connection
    private $pdoConnection = null;

    /**
     * Constructor: Initialization + Open connection with Database
     */
    public function __construct()
    {
        $this->ipDB = DBConfig::$ipDB;
        $this->portDB = DBConfig::$portDB;
        $this->userDB = DBConfig::$userDB;
        $this->passwordDB = DBConfig::$passwordDB;
        $this->dbName = DBConfig::$dbName;
        $this->tableProducts = DBConfig::$tableProducts;
        $this->tableCrawler = DBConfig::$tableCrawler;
        $this->timeoutDB = DBConfig::$timeoutDB;

        $this->initConnection();
    }

    /**
     * Destructor: Closing the connection with Database
     */
    public function __destruct()
    {
        $this->closeConnections();
    }

    /**
     * Init for the connection to database
     */
    public function initConnection()
    {
        try {
            $this->pdoConnection = new PDO("mysql:host=$this->ipDB;port=$this->portDB;dbname=$this->dbName;charset=utf8",
                $this->userDB,
                $this->passwordDB,
                array(
                    PDO::ATTR_TIMEOUT => $this->timeoutDB,
                    PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION
                )
            );
        } catch (PDOException $e) {
            error_log("[Close connection] Error in initConnections()");
            error_log($e);
        }
    }

    /**
     * Close the connection to database and free the resources allocated
     */
    public function closeConnections()
    {
        try {
            $this->pdoConnection = null;
        } catch (PDOException $e) {
            error_log("[Close connection] Error in closeConnections()");
            error_log($e->getMessage());
        }
    }

    /**
     * Check if connection is still present, otherwise re-initialize it
     */
    private function checkConnection()
    {
        if ($this->pdoConnection == null)
            $this->initConnection();
    }

    /**
     * Create tables: for the setup
     */
    public function createTables()
    {
        echo "<br />";
        foreach (DBConfig::$createTables as $tableName => $DDL) {
            echo "<br />Creating the table: " . $tableName . "...";
            $this->pdoConnection->exec($DDL);
        }
    }

    /**
     * Get the list of products
     *
     * @return PDO::FECTH_ASSOC
     */
    public function getProducts()
    {
        $this->checkConnection();
        return $this->pdoConnection->query("SELECT * FROM $this->dbName.$this->tableProducts", PDO::FETCH_ASSOC);
    }

    /**
     * Get crawled data of a specific product in a time interval
     *
     * @param $productName String Name of the product
     * @param $fromDate DateTime Start fetch data from this datetime
     * @param $toDate DateTime End fetch data at this datetime
     * @return PDO::FETCH_ASSOC
     */
    public function getCrawledData($productName, $fromDate, $toDate)
    {
        $this->checkConnection();
        $statement = $this->pdoConnection->prepare("SELECT * FROM $this->dbName.$this->tableCrawler 
                                                    WHERE `product` LIKE :productName AND `timestamp` BETWEEN :fromDate AND :toDate
                                                    LIMIT " . Config::$defaultMaxHistoryResults);
        $statement->execute(array(':productName' => $productName, ':fromDate' => $fromDate, ':toDate' => $toDate));
        return $statement->fetchAll(PDO::FETCH_ASSOC);
    }

    /**
     * Get crawled data of a specific product from "fromDate" until today
     *
     * @param $productName String Name of the product
     * @param $fromDate DateTime Start fetch data from this datetime
     * @return PDO::FETCH_ASSOC
     */
    public function getCrawledDataFrom($productName, $fromDate)
    {
        $this->checkConnection();
//        return $this->pdoConnection->query("SELECT * FROM $this->dbName.$this->tableCrawler WHERE `product` LIKE \"$productName\" AND `timestamp` > \"$fromDate\"", PDO::FETCH_ASSOC);

        $statement = $this->pdoConnection->prepare("SELECT * FROM $this->dbName.$this->tableCrawler   
                                                    WHERE `product` LIKE :productName AND `timestamp` > :fromDate
                                                    ORDER BY `timestamp` DESC
                                                    LIMIT " . Config::$defaultMaxHistoryResults);
        $statement->execute(array(':productName' => $productName, ':fromDate' => $fromDate));
        return $statement->fetchAll(PDO::FETCH_ASSOC);
    }

    /**
     * Get all crawled data of a specific product
     *
     * @param $productName String Name of the product
     * @return PDO::FETCH_ASSOC
     */
    public function getCrawledDataDefault($productName)
    {
        // Y-m-d H:m:s
        $date = date("Y-m-d", strtotime("-" . Config::$defaultHistoryInterval . " day"));
        return $this->getCrawledDataFrom($productName, $date);
    }

    /**
     * Store crawled data of a specific product
     *
     * @param $product String Product name
     * @param $price Number Price in CHF
     * @param $in_stock Number Stock available
     */
    public function createCrawledData($product, $price, $in_stock)
    {
        $this->checkConnection();

        $date = date("Y-m-d H:i:s");
        $statement = $this->pdoConnection->prepare("INSERT INTO $this->dbName.$this->tableCrawler
                                                    (`timestamp`, `product`, `price`, `in_stock`)   
                                                    VALUES (:timestamp, :product, :price, :in_stock)");
        $statement->execute(array(':timestamp' => $date, ':product' => $product->name, ':price' => $price, ':in_stock' => $in_stock));
        $this->updatePriceStats($product, $price, $date);
    }

    private function updatePriceStats($product, $price, $timestamp)
    {
        $this->checkConnection();

        if($product->price_min == null || $price < $product->price_min)
        {
            $statement = $this->pdoConnection->prepare("UPDATE $this->dbName.$this->tableProducts SET `price_min` = :price_min, `timestamp_min` = :timestamp_min WHERE `name` = :name");
            $statement->execute(array(':name' => $product->name, ':price_min' => $price, ':timestamp_min' => $timestamp));
        }

        if($product->price_max == null || $price > $product->price_max)
        {
            $statement = $this->pdoConnection->prepare("UPDATE $this->dbName.$this->tableProducts SET `price_max` = :price_max, `timestamp_max` = :timestamp_max WHERE `name` = :name");
            $statement->execute(array(':name' => $product->name, ':price_max' => $price, ':timestamp_max' => $timestamp));
        }

    }

}
