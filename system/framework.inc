<?php
/**
 * The class Framework is the core of this WebSite
 **
 * @version 1.0
 * @author Misterioso <misterioso@crypted2.com>
 */
require(__DIR__ . '/db.inc');

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
     * Print the product list
     */
    public function printProducts()
    {
        $this->checkFramework();
        $sqlResult = $this->dbClass->getProducts();

        while ($tmpVar = $sqlResult->fetchObject()) {
            //////////////
            // Name
            echo "<td width=\"175px\"><a href=\"$tmpVar->link\" target=\"_blank\" >$tmpVar->name</a></td>";

            //////////////
            // Description
            echo "<td>$tmpVar->description</td>";

            //////////////
            // State
            echo "<td width=\"90px\">ToDo</td>";

            // End of row
            echo "</tr>";
        }
    }
}
