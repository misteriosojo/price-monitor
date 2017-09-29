<?PHP
ini_set('display_errors', 0);
ini_set('log_errors', 1);
ini_set('error_log', __DIR__ . '../error/error.log');
error_reporting(E_ALL);

// Require - Include
//echo(__DIR__);
require_once('../system/config.inc');
require_once("../system/framework.inc");

if (!isset($_GET['fetch']))
    exit(json_encode(json_decode("{}")));


switch ($_GET['fetch']) {
    // To test this, for example: http://localhost/price_monitor/api/index.php?fetch=products
    case 'products':
        $misteriosoFramework = new Framework();
        echo $misteriosoFramework->getProductsJSON();
        break;

    // To test this, for example: http://localhost/price_monitor/api/index.php?fetch=history&product=JBL PRX715 - Set&fromDate=2012-09-01
    case 'history':
        if (!isset($_GET['product']))
            exit(json_encode(json_decode("{ \"error\": \"Parameter 'product' not specified !\" }", false)));

        if (!isset($_GET['fromDate']))
            exit(json_encode(json_decode("{ \"error\": \"Parameter 'fromDate' not specified !\" }", false)));

        $misteriosoFramework = new Framework();
        echo $misteriosoFramework->getProductHistoryJSON($_GET['product'], $_GET['fromDate']);

        break;
    default:
        exit(json_encode(json_decode("{ \"error\": \"Error 404. This GET request doesn't exists !\" }", false)));
}
