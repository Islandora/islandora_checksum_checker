README.txt for the Islandora Checksum Checker module
====================================================

Introduction
============

This module verifies the checksums derived from Islandora object
datastreams and adds a PREMIS 'fixity check' entry to the object's
audit log for each datastream checked. Please note that adding this
entry updates the object (specifically, it changes the object's
lastModifiedDate).

With each run of your site's cron, this module performs checksum
verification on a configurable number of objects' datastreams. When
it has checked all objects (from oldest to newest), it will start
from the beginning (i.e. with the oldest object in your repository)
and repeat the verification cycle.

Installation
============

Same as any Drupal module. There are no prerequisites other than
Islandora. 

However, this module is only useful if you use FedoraCommons to generate
checksums on datastreams. The easiest way to have FedoraCommons generate
checksums is to install and enable the Islandora Checksum module, 
https://github.com/ruebot/islandora_checksum.

Configuration
=============

You should visit the admin form for this module at
admin/islandora/checksum_checker and indicate the datastreams you want 
to have checked.

This module implements hook_cron() to populate a Drupal Queue API queue
of items to check. No configuration is required other than making sure
you are running cron on your Islandora site. However, if you have objects
in your repository that are not viewable by the Drupal anonymous user,
cron will not work as Drupal 7's cron runs as that user. In this case,
you should use the included drush script to populate and process the
queue:

  drush --user=fedoraAdmin run-islandora-checksum-queue
  
Running this script as a Linux cron job will serve the same purpose as
using Drupal's cron. Be sure to select this option in the module's admin
settings (of course, you need to set up the cron job as well).

Author/maintainer
=================

Mark Jordan <mjordan at sfu dot ca>

License
=======

Islandora Checksum Checker is released under the GNU AFFERO GENERAL
PUBLIC LICENSE, version 3. See LICENSE.txt for more information.
