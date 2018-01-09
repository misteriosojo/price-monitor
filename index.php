<?PHP
ini_set('display_errors', 1);
ini_set('log_errors', 1);
ini_set('error_log', __DIR__.'/error/error.log');
error_reporting(E_ALL);

// Require - Include
require_once(__DIR__ . '/system/config.inc');
require_once(__DIR__ . "/system/framework.inc");

if(!isset($_GET['page']))
    $_GET['page'] = "home";

switch ($_GET['page']) {
    case 'home':
        $misteriosoFramework = new Framework();
        $pageTitle = "Overview";
        include(__DIR__ . "/theme/header.inc");
        include(__DIR__.'/script/home.php');
        break;
    case 'products':
        $misteriosoFramework = new Framework();
        $pageTitle = "Product list";
        include(__DIR__ . "/theme/header.inc");
        include(__DIR__ . '/script/products.php');
        break;
    default:
        $pageTitle = "Page not found";
        header('HTTP/1.1 404 Not Found');
        include(__DIR__ . "/theme/header.inc");
        include(__DIR__.'/script/404.php');
        break;
}
include(__DIR__ . "/theme/footer.inc");
