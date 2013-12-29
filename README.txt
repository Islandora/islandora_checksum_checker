README.txt for the Islandora Checksum Checker module
====================================================

Introduction
============

This module verifies the checksums derived from Islandora object
datastreams and adds an entry to the object's audit log. Adding this
entry updates the object (i.e., it changes the object's lastModifiedDate).

Installation
============

Same as any Drupal module. Only prerequisite is theIslandora
Checksum module, https://github.com/ruebot/islandora_checksum.

Configuration
=============

You should visit the admin form for this module at admin/islandora/checksum_checker
and indicate the datastreams you want to have checked.

Also, this module implements hook_cron() to populate a Drupal Queue API
queue of items to check. No configuration is required other than making sure
you are running cron on your Islandora site.

Author/maintainer
=================

Mark Jordan <mjordan at sfu dot ca>

License
=======

Islandora BagIt is released under the GNU AFFERO GENERAL PUBLIC LICENSE,
version 3. See LICENSE.txt for more information.
