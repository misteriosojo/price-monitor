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

        $i = 0;

        while ($tmpProduct = $productList->fetchObject()) {
//            $crawlResults = $this->dbClass->getCrawledDataDefault($tmpProduct->name);
//            echo " For $tmpProduct->name the number of results is: " . count($crawlResults) . " <br>";

            $productData = json_decode($this->getProductHistoryJSON($tmpProduct->name, '2012-09-01'));
            $this->drawProductChart($i, $productData);

            $i++;
        }

    }

    private function drawProductChart($canvasID, $productData)
    {
        $allData = $productData->data;

        $allTimestamp = array();
        $allPrice = array();
        $allInstock = array();

        $dataForChart = array();

        foreach ($allData as $oneData) {
            array_push($allTimestamp, $oneData->timestamp);
            array_push($allPrice, $oneData->price);
            array_push($allInstock, $oneData->in_stock);

        }


        ?>

        <div style="width:80%;height:100%;">
            <canvas id="canvas<?= $canvasID; ?>"></canvas>
        </div>
        </br>
        <script>
            function addLoadEvent(func) {
                var oldonload = window.onload;
                if (typeof window.onload != 'function') {
                    window.onload = func;
                } else {
                    window.onload = function() {
                        if (oldonload) {
                            oldonload();
                        }
                        func();
                    }
                }
            }

            addLoadEvent(function () {
                var ctx = document.getElementById("canvas<?= $canvasID; ?>").getContext("2d");
                var aaa = new Chart(ctx, {
                    type: 'line',
                    data: {
                        datasets: [{
                            label: "Price",
                            borderColor: 'blue',
                            fill: true,
                            backgroundColor : '#009fff',
                            data: [ <?PHP foreach ($allData as $oneData) { ?>
                                {
                                    t: '<?= $oneData->timestamp; ?>',
                                    y: '<?= $oneData->price; ?>'
                                } <?= next($allData) ? "," : "" ?> <?PHP } ?>
                            ]
                        }, {
                            label: "In Stock",
                            borderColor: 'black',
                            fill: true,
                            backgroundColor : '#4e4f4f',
                            hidden: true,
                            data: [ <?PHP foreach ($allData as $oneData) { ?>
                                {
                                    t: '<?= $oneData->timestamp; ?>',
                                    y: '<?= $oneData->in_stock; ?>'
                                } <?= next($allData) ? "," : "" ?> <?PHP } ?>
                            ]
                        }]
                    },
                    options: {
                        responsive: true,
                        title: {
                            display: true,
                            text: "Product: <?= $productData->product; ?>",
                            fontSize: 25,
                            fontColor: 'black'
                        },
                        scales: {
                            xAxes: [{
                                type: "time",
                                time: {
                                    unit: 'day'
                                },
                                display: true,
                                scaleLabel: {
                                    display: true,
                                    labelString: 'Date'
                                }
                            }],
                            yAxes: [{
                                display: true,
                                scaleLabel: {
                                    display: true,
                                    labelString: 'price'
                                }
                            }]
                        }
                    }
                });


            });
        </script>

        <?PHP
    }

}
