<?php
require(__DIR__ . '/db.inc');

/**
 * The class Framework is the core of this WebSite
 **
 * @version 1.0
 * @author Misterioso <misterioso@crypted2.com>
 */
class Framework
{
    // Variable for communicate with the DatabaseManager
    private $dbClass;

    /**
     * Constructor of the Framework
     */
    public function __construct()
    {
        $this->initFramework();
    }

    /**
     * Destruct of the Framework
     */
    public function __destruct()
    {
        $this->dbClass = null;
    }

    /**
     *  Init the Framework: create instance of DatabaseManager
     */
    public function initFramework()
    {
        $this->dbClass = new DatabaseManager();
    }

    /**
     * Check if dbClass is still present, otherwise re-initialize it
     */
    private function checkFramework()
    {
        if ($this->dbClass == null)
            $this->initFramework();
    }

    /**
     * Get products
     * @return mixed
     */
    public function getProducts()
    {
        return $this->dbClass->getProducts();
    }

    /**
     * Get products in JSON format
     * @return string String JSON encoded string
     */
    public function getProductsJSON()
    {
        $productsResult = $this->dbClass->getProducts();
        return json_encode($productsResult->fetchAll());
    }

    /**
     * Get product history in JSON format
     * @param $productName String Product name
     * @param $fromDate String Data will be fetched starting from this date
     * @return string String JSON encoded string
     */
    public function getProductHistoryJSON($productName, $fromDate)
    {
        $crawlResults = $this->dbClass->getCrawledDataDefault($productName);

        $toReturn = json_decode("{}");
        $toReturn->product = $productName;
        $toReturn->fromDate = $fromDate;
        $toReturn->data = $crawlResults;

        return json_encode($toReturn);
    }

    /**
     * Print the product list
     */
    public function printProducts()
    {
        $this->checkFramework();
        $sqlResult = $this->dbClass->getProducts();
        if ($sqlResult == null) {
            error_log("[printProducts] Ops, sqlResult is null");
            return;
        }

        while ($tmpVar = $sqlResult->fetchObject()) {
            //////////////
            // Name
            echo "<td width=\"175px\"><a href=\"$tmpVar->link\" target=\"_blank\" >$tmpVar->name</a></td>";

            //////////////
            // Description
            echo "<td>$tmpVar->description</td>";

            //////////////
            // State
            echo "<td width=\"80px\">ToDo</td>";

            // End of row
            echo "</tr>";
        }
    }

    /**
     * Print crawled data
     */
    public function printCrawledDataAll()
    {
        $this->checkFramework();
        $productList = $this->dbClass->getProducts();

        $i=0;

        while ($tmpProduct = $productList->fetchObject()) {
            $this->reserveCanvas($i);

            $crawlResults = $this->dbClass->getCrawledDataDefault($tmpProduct->name);

//            echo " For $tmpProduct->name the number of results is: " . $crawlResults->rowCount() . " <br>";
            echo " For $tmpProduct->name the number of results is: " . count($crawlResults) . " <br>";

            $this->getProductHistoryJSON($tmpProduct->name, '2012-09-01');
            $i++;
        }

    }

    private function reserveCanvas($canvasID)
    {
        echo "<div style=\"width:80%;height:100%;\"><canvas id=\"canvas$canvasID\"></canvas></div>";
    }

}
