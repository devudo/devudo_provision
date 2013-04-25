;
; This makefile should be used by devmaster-install
; 

core = 6.x
api = 2

projects[drupal][type] = "core"

projects[devmaster][type] = "profile"
projects[devmaster][download][type] = "git"
projects[devmaster][download][url] = "git@github.com:devudo/devmaster_plus.git"
projects[devmaster][download][branch] = "6.x-1.x"
