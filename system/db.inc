<?php

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

require_once(__DIR__ . '/../system/config.inc');

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

        return $this->pdoConnection->query("SELECT * FROM $this->dbName.$this->tableProducts"
            , PDO::FETCH_ASSOC);
    }
}
