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
    static $toolName = "PriceMonitor";
    static $redirectTimeout = 5;
    static $defaultHistoryInterval = 1000; // days
    static $defaultMaxHistoryResults = 100; // count
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
    static $tableProducts = "products"; // Table of product list
    static $tableCrawler = "crawler"; // Table od crawled data

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
                          PRIMARY KEY (`id`)
                        ) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=latin1;"
    );
}
