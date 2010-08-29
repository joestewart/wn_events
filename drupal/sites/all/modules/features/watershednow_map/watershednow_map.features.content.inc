<?php

/**
 * Implementation of hook_content_default_fields().
 */
function watershednow_map_content_default_fields() {
  $fields = array();

  // Exported field: field_attachments
  $fields['map_feature-field_attachments'] = array(
    'field_name' => 'field_attachments',
    'type_name' => 'map_feature',
    'display_settings' => array(
      'weight' => '1',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '0',
    'multiple' => '1',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '1',
    'list_default' => 0,
    'description_field' => '1',
    'widget' => array(
      'file_extensions' => 'txt pdf doc jpg png gif xls',
      'file_path' => 'attachments',
      'progress_indicator' => 'bar',
      'max_filesize_per_file' => '',
      'max_filesize_per_node' => '',
      'filefield_sources' => array(
        'reference' => 'reference',
        'attach' => 0,
        'remote' => 0,
      ),
      'filefield_source_attach_path' => 'file_attach',
      'filefield_source_attach_absolute' => '0',
      'filefield_source_attach_mode' => 'copy',
      'filefield_source_autocomplete' => '1',
      'insert' => 0,
      'insert_styles' => array(
        'auto' => 0,
        'link' => 0,
        'image' => 0,
        'imagecache_thumbnail_large' => 0,
        'imagecache_thumbnail_medium' => 0,
        'imagecache_thumbnail_small' => 0,
        'imagecache_web' => 0,
      ),
      'insert_default' => 'auto',
      'insert_class' => '',
      'insert_width' => '',
      'label' => 'Attachments',
      'weight' => '1',
      'description' => 'Attach supporting documents and files to this donation page.',
      'type' => 'filefield_widget',
      'module' => 'filefield',
    ),
  );

  // Exported field: field_get_involved
  $fields['map_feature-field_get_involved'] = array(
    'field_name' => 'field_get_involved',
    'type_name' => 'map_feature',
    'display_settings' => array(
      'weight' => 0,
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereference',
    'required' => '0',
    'multiple' => '5',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'donation' => 'donation',
      'event' => 'event',
      'take_action' => 'take_action',
      'page' => 0,
      'update' => 0,
      'update_feed' => 0,
      'map_feature' => 0,
      'webform' => 0,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => 60,
      'default_value' => array(
        '0' => array(
          'nid' => NULL,
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Associated action pages',
      'weight' => 0,
      'description' => 'Select those "Take Action" and donation pages associated with this watershed feature.',
      'type' => 'nodereference_buttons',
      'module' => 'nodereference',
    ),
  );

  // Exported field: field_image_assets
  $fields['map_feature-field_image_assets'] = array(
    'field_name' => 'field_image_assets',
    'type_name' => 'map_feature',
    'display_settings' => array(
      'weight' => '8',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '0',
    'multiple' => '1',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '0',
    'list_default' => 1,
    'description_field' => '0',
    'widget' => array(
      'file_extensions' => 'png gif jpg jpeg',
      'file_path' => 'image_assets',
      'progress_indicator' => 'bar',
      'max_filesize_per_file' => '',
      'max_filesize_per_node' => '',
      'max_resolution' => '0',
      'min_resolution' => '0',
      'alt' => '',
      'custom_alt' => 1,
      'title' => '',
      'custom_title' => 1,
      'title_type' => 'textfield',
      'default_image' => NULL,
      'use_default_image' => 0,
      'filefield_sources' => array(
        'reference' => 'reference',
        'attach' => 'attach',
        'remote' => 0,
      ),
      'filefield_source_attach_path' => 'file_attach',
      'filefield_source_attach_absolute' => '0',
      'filefield_source_attach_mode' => 'copy',
      'filefield_source_autocomplete' => '1',
      'insert' => 1,
      'insert_styles' => array(
        'auto' => 'auto',
        'image' => 'image',
        'imagecache_thumbnail_large' => 'imagecache_thumbnail_large',
        'imagecache_thumbnail_medium' => 'imagecache_thumbnail_medium',
        'imagecache_thumbnail_small' => 'imagecache_thumbnail_small',
        'imagecache_web' => 'imagecache_web',
        'link' => 0,
      ),
      'insert_default' => 'imagecache_web',
      'insert_class' => '',
      'insert_width' => '',
      'wysiwyg_imagefield' => TRUE,
      'label' => 'Image assets',
      'weight' => '8',
      'description' => '',
      'type' => 'imagefield_widget',
      'module' => 'imagefield',
    ),
  );

  // Exported field: field_wkt
  $fields['map_feature-field_wkt'] = array(
    'field_name' => 'field_wkt',
    'type_name' => 'map_feature',
    'display_settings' => array(
      'weight' => '-2',
      'parent' => '',
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'openlayers_map_map_picker',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'openlayers_wkt',
    'required' => '1',
    'multiple' => '1',
    'module' => 'openlayers_cck',
    'active' => '1',
    'openlayers_cck_feature_types' => array(
      'point' => 'point',
      'path' => 'path',
      'polygon' => 'polygon',
    ),
    'widget' => array(
      'openlayers_cck_preset_map' => 'map_picker',
      'openlayers_behaviors' => array(
        'openlayers_behavior_zoomtolayer' => array(
          'enabled' => 0,
          'options' => array(
            'zoomtolayer' => 'openlayers_cck_vector_layer',
            'point_zoom_level' => '5',
          ),
        ),
      ),
      'keep_points' => 0,
      'position' => '10',
      'default_value' => array(
        '0' => array(
          'openlayers_wkt' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Geolocation',
      'weight' => '-2',
      'description' => 'Enter the location(s) of this feature. You may create any combination of points, polylines, and polygons. Your entry will be stored as <a hre="http://en.wikipedia.org/wiki/Well_Known_Text" target="_blank">well-known text</a>. You can also search for an address to get started, but each time you search, your previous entry will be erased. (<em>Hint:</em> When drawing shapes, double-click the map to complete a line or polygon shape.)',
      'type' => 'openlayers_geocoder_widget',
      'module' => 'openlayers_geocoder',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Associated action pages');
  t('Attachments');
  t('Geolocation');
  t('Image assets');

  return $fields;
}