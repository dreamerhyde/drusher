Drusher
=======

## Description
Drusher is a drupal commander let you set your enviroment variables by using Drush
to production or development. At the same time, this module will set drupal vars,
modules to fit your enviroment.

I will put more useful command to this module.

## Standard use
```drush drusher-set-env(env)```

## Set to dev enviroment
```drush drusher-set-env(env) dev```
* Preprocess css, js
* Open cache, block cache
* Open page compression
* Disable error level
* Disable modules devel, devel_generate, views_ui, update, syslog, dblog, field_ui

## Set to prod enviroment
```drush drusher-set-env(env) prod```
* Reverse from dev

Completed the command will automatically clear all cache