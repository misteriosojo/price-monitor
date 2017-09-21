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

<?PHP
$resultStats = $misteriosoFramework->getBugsStats();
$bugsTotal = $resultStats["total"];
$bugsSolved = $resultStats["done"];
$bugsSuspended = $resultStats["todo"];
$bugsRejected = $resultStats["rejected"];
$bugsNew = $bugsTotal - $bugsSolved - $bugsSuspended - $bugsRejected;

$ptcRejected = (int)($bugsRejected / $bugsTotal * 100);
$ptcSuspended = (int)($bugsSuspended / $bugsTotal * 100);
$ptcSolved = (int)($bugsSolved / $bugsTotal * 100);
$ptcNew = 100 - $ptcSolved - $ptcRejected - $ptcSuspended;


?>

<!-- stats !-->
<table id="statistics">
    <tr>
        <td width="500px">
            <button class="btn btn-primary taskTotal" type="button">Vista di insieme.<br />Numero di Bugs totali:<br /><span class="badge"> <?PHP echo $bugsTotal ?> </span> </button><br />
            <br />
            <div class="progress">
                <div class="progress-bar progress-bar-info" style="width: <?PHP echo $ptcNew ?>%">
                    <span><?PHP echo $ptcNew ?>% Nuovi</span>
                </div>
                <div class="progress-bar progress-bar-success" style="width: <?PHP echo $ptcSolved ?>%">
                    <span><?PHP echo $ptcSolved ?>% Risolti</span>
                </div>
                <div class="progress-bar progress-bar-warning progress-bar-striped" style="width: <?PHP echo $ptcSuspended ?>%">
                    <span><?PHP echo $ptcSuspended ?>% Working</span>
                </div>
                <div class="progress-bar progress-bar-danger" style="width: <?PHP echo $ptcRejected ?>%">
                    <span><?PHP echo $ptcRejected ?>% Non Risolti</span>
                </div>
            </div>
        </td>
        <td>
            <div class="taskNew" id="taskNew" data-dimension="140" data-text="<?PHP echo $ptcNew ?>%" data-info="Nuovi" data-width="15" data-fontsize="20" data-percent="<?PHP echo $ptcNew ?>" data-fgcolor="#5bc0de" data-bgcolor="#BEBEBE" data-fill="#ddd"></div><br />
            <button class="btn btn-info taskTotal" type="button"> Nuovi: <span class="badge"><?PHP echo $bugsNew ?></span> </button>
        </td>
        <td>
            <div class="taskdone" id="taskDone" data-dimension="140" data-text="<?PHP echo $ptcSolved ?>%" data-info="Risolti" data-width="15" data-fontsize="20" data-percent="<?PHP echo $ptcSolved ?>" data-fgcolor="#5cb85c" data-bgcolor="#BEBEBE" data-fill="#ddd"></div><br />
            <button class="btn btn-success taskTotal" type="button"> Risolti: <span class="badge"><?PHP echo $bugsSolved ?></span> </button>
        </td>
        <td>
            <div class="taskToDo" id="taskToDo" data-dimension="140" data-text="<?PHP echo $ptcSuspended ?>%" data-info="Da Risolvere" data-width="15" data-fontsize="20" data-percent="<?PHP echo $ptcSuspended ?>" data-fgcolor="#ec971f" data-bgcolor="#BEBEBE" data-fill="#ddd"></div><br />
            <button class="btn btn-warning taskTotal" type="button"> Da Risolvere: <span class="badge"><?PHP echo $bugsSuspended ?></span> </button>
        </td>
        <td>
            <div class="taskRejected" id="taskRejected" data-dimension="140" data-text="<?PHP echo $ptcRejected ?>%" data-info="Non Risolti" data-width="15" data-fontsize="20" data-percent="<?PHP echo $ptcRejected ?>" data-fgcolor="#ac2925" data-bgcolor="#BEBEBE" data-fill="#ddd"></div><br />
            <button class="btn btn-danger taskTotal" type="button"> Non Risolti: <span class="badge"><?PHP echo $bugsRejected ?></span> </button>
        </td>
    </tr>
</table>
<br />
<!-- Table example !-->
<table class='table table-responsive table-bordered'>

    <tr class="bg-primary">
        <td>#</td>
        <td>Bug segnalato il</td>
        <td>Tipo di bug</td>
        <td>Inviato da</td>
        <td>Bug</td>
        <td>Descrizione</td>
        <td>Stato</td>
        <td>Bug chiuso il</td>
    </tr>

    <?PHP $misteriosoFramework->printBugList(); ?>

</table>

