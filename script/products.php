<script type="text/javascript">
    document.getElementById("navProducts").className = "active";
</script>
<!-- Text header example !-->
<div class="page-header">
    <h1><?PHP echo Config::$toolName." - ".$pageTitle ?></h1>
</div>

<!-- Message box example !-->
<div class="alert alert-info">
    <strong>Welcome!</strong> In this page you can see the list of products monitored!
</div>

<table class='table table-responsive table-bordered'>

    <tr class="bg-primary">
        <td>Name</td>
        <td>Description</td>
        <td>Crawling Active</td>
        <td>Price Min</td>
        <td>Timestamp Price Min</td>
        <td>Price Max</td>
        <td>Timestamp Price Min</td>
    </tr>

    <?PHP $misteriosoFramework->printProducts(); ?>

</table>

