<script type="text/javascript">
    document.getElementById("navHome").className = "active";
</script>
<!-- Text header example !-->
<div class="page-header">
    <h1><?PHP echo Config::$toolName." - ".$pageTitle ?></h1>
</div>

<!-- Message box example !-->
<div class="alert alert-info">
    <strong>Welcome!</strong> In this page you'll see an overview of this tool!
</div>

<?PHP
$resultStats = $misteriosoFramework->getGeneralStats();
$taskTotal = $resultStats["total"];
$taskDone = $resultStats["done"];
$taskToDo = $resultStats["todo"];
$taskRejected = $resultStats["rejected"];
$taskNew = $taskTotal - $taskDone - $taskToDo - $taskRejected;

$ptcRejected = (int)($taskRejected / $taskTotal * 100);
$ptcSuspended = (int)($taskToDo / $taskTotal * 100);
$ptcDone = (int)($taskDone / $taskTotal * 100);
$ptcNew = 100 - $ptcDone - $ptcRejected - $ptcSuspended;


?>

<!-- stats !-->
<table id="statistics">
    <tr>
        <td width="500px">
            <button class="btn btn-primary taskTotal" type="button">Vista di insieme.<br />Numero di task totali:<br /><span class="badge"> <?PHP echo $taskTotal ?> </span> </button><br />
            <br />
            <div class="progress">
                <div class="progress-bar progress-bar-info" style="width: <?PHP echo $ptcNew ?>%">
                    <span><?PHP echo $ptcNew ?>% Nuovi</span>
                </div>
                <div class="progress-bar progress-bar-success" style="width: <?PHP echo $ptcDone ?>%">
                    <span><?PHP echo $ptcDone ?>% Completati</span>
                </div>
                <div class="progress-bar progress-bar-warning progress-bar-striped" style="width: <?PHP echo $ptcSuspended ?>%">
                    <span><?PHP echo $ptcSuspended ?>% Sospesi</span>
                </div>
                <div class="progress-bar progress-bar-danger" style="width: <?PHP echo $ptcRejected ?>%">
                    <span><?PHP echo $ptcRejected ?>% Rifiutati</span>
                </div>
            </div>
        </td>
        <td>
            <div class="taskNew" id="taskNew" data-dimension="140" data-text="<?PHP echo $ptcNew ?>%" data-info="Nuovi" data-width="15" data-fontsize="20" data-percent="<?PHP echo $ptcNew ?>" data-fgcolor="#5bc0de" data-bgcolor="#BEBEBE" data-fill="#ddd"></div><br />
            <button class="btn btn-info taskTotal" type="button"> Task Nuovi: <span class="badge"><?PHP echo $taskNew ?></span> </button>
        </td>
        <td>
            <div class="taskdone" id="taskDone" data-dimension="140" data-text="<?PHP echo $ptcDone ?>%" data-info="Completati" data-width="15" data-fontsize="20" data-percent="<?PHP echo $ptcDone ?>" data-fgcolor="#5cb85c" data-bgcolor="#BEBEBE" data-fill="#ddd"></div><br />
            <button class="btn btn-success taskTotal" type="button"> Task Completati: <span class="badge"><?PHP echo $taskDone ?></span> </button>
        </td>
        <td>
            <div class="taskToDo" id="taskToDo" data-dimension="140" data-text="<?PHP echo $ptcSuspended ?>%" data-info="Sospesi" data-width="15" data-fontsize="20" data-percent="<?PHP echo $ptcSuspended ?>" data-fgcolor="#ec971f" data-bgcolor="#BEBEBE" data-fill="#ddd"></div><br />
            <button class="btn btn-warning taskTotal" type="button"> Task In sospeso: <span class="badge"><?PHP echo $taskToDo ?></span> </button>
        </td>
        <td>
            <div class="taskRejected" id="taskRejected" data-dimension="140" data-text="<?PHP echo $ptcRejected ?>%" data-info="Rifiutati" data-width="15" data-fontsize="20" data-percent="<?PHP echo $ptcRejected ?>" data-fgcolor="#ac2925" data-bgcolor="#BEBEBE" data-fill="#ddd"></div><br />
            <button class="btn btn-danger taskTotal" type="button"> Task Rifiutati: <span class="badge"><?PHP echo $taskRejected ?></span> </button>
        </td>
    </tr>
</table>
<br />

<!-- Table example !-->
<table class='table table-responsive table-bordered'>

    <tr class="bg-primary">
        <td width="20px">#</td>
        <td width="160px">Task aperto il</td>
        <td width="300px">Task</td>
        <td>Descrizione</td>
        <td width="200px">Stato</td>
        <td width="160px">Task chiuso il</td>
    </tr>

    <?PHP $misteriosoFramework->printGeneralList(); ?>

</table>

