# Note: Work in progress...

# [PHP] Price monitor
Track a price online storing data in a Database and visualize the data via graphs.

# Installation

Apache:     
.htaccess already provided in this repo

Nginx:  
```bash
location ~ /(crawler|include) {
 deny all;
}  
  
# Add this block only after the "deny" block
location ~ \.php$ {
  # do stuff to enable php
}
```