# [PHP] Price monitor - Gear4Music
Track a price online storing the data in a database and visualize the data using chart.js  

## Installation
**First configuration**  
Edit the configuration file in `system/config.inc` specifying the connection data to your database and the names of the DB+Tables.
As wrote in the comments, the user used for this application must have following permissions: `Select, Insert, Create, Drop`.
Otherwise it will not be possible to create the database tables.
  
Resuming, the fields to check/update are:  
- `$ipDB`: Database IP address
- `$portDB`: Database port
- `$timeoutDB`: Connection Timeout (in seconds)
- `$userDB`: Username
- `$passwordDB`: Password
- `$dbName`: Database name
- `$tableProducts`: Table name where products are stored (if you edit this, change also the name in DDL below)
- `$tableCrawler`: Table name where crawled data are stored (if you edit this, change also the name in DDL below)
  
**Execute the installation**  
Allow temporary the folder `system` and execute the file `system/install.php`. This will create the necessary tables.

**Webserver quick configuration**  
Apache:     
.htaccess already provided in this repo

Nginx:  
```bash
location ~ /(error|script|system) {
 deny all;
}  
  
# Add this block only after the "deny" block
location ~ \.php$ {
  # do stuff to enable php
}
```

## Configuration
The variables are briefly explained using an inline comment:
- `$toolName`: Name of this tool
- `$redirectTimeout`: Waiting time to be redirected to the homepage when a 404 error occurs
- `$defaultHistoryInterval`: Default days used as elapsed time from "now"
- `$defaultMaxHistoryResults`: Max results used to build the charts
  
... to be continued...  
