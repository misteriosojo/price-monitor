<?php
ini_set('display_errors', 1);
ini_set('log_errors', 1);
ini_set('error_log', __DIR__ . '/../../error/error.log');
error_reporting(E_ALL);

// Require - Include
require_once(__DIR__ . '/../config.inc');
require_once(__DIR__ . "/../framework.inc");

$misteriosoFramework = new Framework();
$products = $misteriosoFramework->getProducts();

if ($products == null) {
    error_log("[crawler] Ops, sqlResult is null");
    return;
}

while ($tmpProduct = $products->fetchObject()) {

    // If crawling_active is 0, the product will be skipped
    if (!$tmpProduct->crawling_active)
        continue;

    $doc = new DOMDocument();
    libxml_use_internal_errors(true);
    $doc->loadHTMLFile($tmpProduct->link);
    libxml_clear_errors();
    $finder = new DomXPath($doc);
    $classname = "main-price";
    $nodesMatched = $finder->query("//div[contains(@class, '$classname')]/*/span[contains(@itemprop, 'price')]");

    // Check if price information is available
    if ($nodesMatched && ($price = $nodesMatched->item(0)->getAttribute('content'))) {

        // Replace all non alpha char (without this operation, numbers like 1'157 will be read in a wrong way)
        preg_replace("/[^A-Za-z0-9 ]/", '', $price);

        $nodesMatched = $finder->query("//div[contains(@class, 'stock-information')]/p");
        $stockRawInformation = $nodesMatched->item(0)->nodeValue;

        preg_match('/\d+/', $stockRawInformation, $matches);
        $in_stock = $matches ? $matches[0] : null;
        $misteriosoFramework->createCrawledData($tmpProduct, $price, $in_stock);
    } else {
        error_log("[crawler] Product not available: " . $tmpProduct->name);
    }
}







