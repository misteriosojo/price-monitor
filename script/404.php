<div class="page-header">
    <h1><?PHP echo Config::$toolName." - ".$pageTitle ?></h1>
</div>

<!-- Message box example !-->
<div class="alert alert-danger">
    <strong>Error 404!</strong> <br>
    Mmmhhh... The page doesn't exist... What are you looking for ?<br>
    <br>
    You'll be redirected to the HomePage in <span id="timerRedirect">10</span> seconds...
</div>


<!-- Display CountDown and redirect to the home -->
<script type="text/javascript">

    function Redirect()
    {
        window.location="index.php";
    }

    function startTimer(duration, display) {
        var timer = duration, minutes, seconds;
        setInterval(function () {
            seconds = parseInt(timer % 60, 10);

           display.textContent =  seconds < 10 ? "0" + seconds : seconds;

            if(seconds === 0)
                Redirect();

            if (--timer < 0) {
                timer = duration;
            }
        }, 1000);
    }

    window.onload = function () {
        var delaySeconds = 9;
        var display = document.querySelector('#timerRedirect');
        startTimer(delaySeconds, display);
    }

</script>