README.txt for the Islandora Checksum Checker module
====================================================

Introduction
============

This module verifies the checksums derived from Islandora object
datastreams and adds a PREMIS 'fixity check' entry to the object's
audit log for each datastream checked. Please note that adding this
entry updates the object (specifically, it changes the object's
lastModifiedDate).

Installation
============

Same as any Drupal module. The only prerequisite is the Islandora
Checksum module, https://github.com/ruebot/islandora_checksum.

Configuration
=============

You should visit the admin form for this module at
admin/islandora/checksum_checker and indicate the datastreams you want 
to have checked.

Also, this module implements hook_cron() to populate a Drupal Queue API
queue of items to check. No configuration is required other than making sure
you are running cron on your Islandora site.

Author/maintainer
=================

Mark Jordan <mjordan at sfu dot ca>

License
=======

Islandora Checksum Checker is released under the GNU AFFERO GENERAL
PUBLIC LICENSE, version 3. See LICENSE.txt for more information.
