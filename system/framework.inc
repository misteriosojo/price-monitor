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
    public function __construct(){
        $this->initFramework();
    }

    /**
     * Destruct of the Framework
     */
    public function __destruct(){
        $this->dbClass = null;
    }

    /**
     *  Init the Framework: create instance of DatabaseManager
     */
    public function initFramework(){
        $this->dbClass = new DatabaseManager();
    }

    /**
     * Check if dbClass is still present, otherwise re-initialize it
     */
    private function checkFramework(){
        if($this->dbClass == null)
            $this->initFramework();
    }

    /**
     * Get products
     * @return mixed
     */
    public function getProducts(){
        return $this->dbClass->getProducts();
    }
}
