<?php

function devudo_drush_commands() {


}

/**
 * implements drush_hook_pre_hosting_task()
function drush_devudo_pre_hosting_task() {
  drush_log('[DEVUDO] drush_devudo_pre_hosting_task() invoked.');

  $task = &drush_get_context('HOSTING_TASK');
  $task_node = $task->ref;
      
    if ($task->task_type == 'install' && $task->ref->type == 'site') {
      // CREATE USER!
      

      drush_log('[DEVUDO] Task: ' . print_r($task, 1));
//      drush_log('[DEVUDO]: ' . print_r($task, 1));
    }
  
}


 */
