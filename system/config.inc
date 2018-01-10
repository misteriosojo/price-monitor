<?php
/**
 * This file contains some configurations
 *
 * @version 1.0
 * @author Misterioso <misterioso@crypted2.com>
 */


/**********************************
 * Configurations for the WebSite *
 **********************************/
class Config
{
    static $toolName = "PriceMonitor"; // Name of this tool
    static $redirectTimeout = 5; // Waiting time to be redirected to the homepage when a 404 error occurs
    static $defaultHistoryInterval = 1000; // Default days used as elapsed time from "now"
    static $defaultMaxHistoryResults = 100; // Max results used to build the charts
}


/************************************
 * Configurations for the Database  *
 ************************************/
class DBConfig
{
    // Ip address and Port to connect to DB
    static $ipDB = "localhost"; // Ip address to connect to DB  ToDo: Change me
    static $portDB = 3306; // Port to connect to DB (default: 3306)  ToDo: Change me
    static $timeoutDB = 3; // Seconds available to reach the DB

    // Account Database: Permissions --> Select + Insert + Create + Drop
    static $userDB = "price_monitor"; // Username to connect to DB.  ToDo: Change me
    static $passwordDB = "price_monitor"; // Password to connect to DB  ToDo: Change me

    // Database data
    static $dbName = "price_monitor"; // Database name  ToDo: Change me
    static $tableProducts = "products"; // Table of product list (if you edit this, change also the name in DDL below)
    static $tableCrawler = "crawler"; // Table od crawled data (if you edit this, change also the name in DDL below)

    // DDL to create the tables
    static $createTables = array(
        "crawler" => "DROP TABLE IF EXISTS `crawler`;
                        CREATE TABLE `crawler` (
                          `id` INT(11) NOT NULL AUTO_INCREMENT,
                          `timestamp` DATETIME DEFAULT NULL,
                          `product` VARCHAR(255) DEFAULT NULL,
                          `price` DECIMAL(10,0) DEFAULT NULL,
                          `in_stock` VARCHAR(255) DEFAULT NULL,
                          PRIMARY KEY (`id`)
                        ) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=latin1;",
        "products" => " DROP TABLE IF EXISTS `products`;
                        CREATE TABLE `products` (
                          `id` INT(11) NOT NULL AUTO_INCREMENT,
                          `name` VARCHAR(255) DEFAULT NULL,
                          `link` VARCHAR(255) DEFAULT NULL,
                          `description` TEXT,
                          `crawling_active` TINYINT(1) DEFAULT '1',
                          `price_min` INT(11) DEFAULT NULL,
                          `timestamp_min` DATETIME DEFAULT NULL,
                          `price_max` INT(11) DEFAULT NULL,
                          `timestamp_max` DATETIME DEFAULT NULL,
                          PRIMARY KEY (`id`)
                        ) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=latin1;"
    );
}
