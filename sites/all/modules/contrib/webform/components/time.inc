<?php
// $Id: time.inc,v 1.24.2.9 2010/06/30 04:27:14 quicksketch Exp $

/**
 * @file
 * Webform module time component.
 */

// Time depends on functions provided by date.
webform_component_include('date');

/**
 * Implementation of _webform_defaults_component().
 */
function _webform_defaults_time() {
  return array(
    'name' => '',
    'form_key' => NULL,
    'pid' => 0,
    'weight' => 0,
    'value' => '',
    'mandatory' => 0,
    'email' => 1,
    'extra' => array(
      'timezone' => 'user',
      'hourformat' => '12-hour',
      'description' => '',
    ),
  );
}

/**
 * Implementation of _webform_theme_component().
 */
function _webform_theme_time() {
  return array(
    'webform_time' => array(
      'arguments' => array('element' => NULL),
    ),
    'webform_display_time' => array(
      'arguments' => array('element' => NULL),
    ),
  );
}

/**
 * Implementation of _webform_edit_component().
 */
function _webform_edit_time($component) {
  $form = array();
  $form['value'] = array(
    '#type' => 'textfield',
    '#title' => t('Default value'),
    '#default_value' => $component['value'],
    '#description' => t('The default value of the field.') . '<br />' . t('Accepts a time in any <a href="http://www.gnu.org/software/tar/manual/html_chapter/Date-input-formats.html">GNU Date Input Format</a>. Strings such as now, +2 hours, and 10:30pm are all valid.'),
    '#size' => 60,
    '#maxlength' => 127,
    '#weight' => 0,
  );
  $form['extra']['timezone'] = array(
    '#type' => 'radios',
    '#title' => t('Timezone'),
    '#default_value' => empty($component['extra']['timezone']) ? 'user' : $component['extra']['timezone'],
    '#description' => t('Adjust the default time value according to a specific timezone.'),
    '#options' => array('user' => t('User timezone'), 'site' => t('Website timezone')),
    '#weight' => 0,
    '#access' => variable_get('configurable_timezones', 1) && module_exists('date_timezone'),
  );
  $form['display']['hourformat'] = array(
    '#type' => 'radios',
    '#title' => t('Time Format'),
    '#default_value' => isset($component['extra']['hourformat']) ? $component['extra']['hourformat'] : '12-hour',
    '#description' => t('Format the display of the time in 12 or 24 hours.'),
    '#options' => array('12-hour' => t('12-hour (am/pm)'), '24-hour' => t('24-hour')),
    '#weight' => 2,
    '#parents' => array('extra', 'hourformat'),
  );
  return $form;
}

/**
 * Implementation of _webform_render_component().
 */
function _webform_render_time($component, $value = NULL) {
  if (drupal_strlen($component['value']) > 0) {
    // Adjust the time based on the user or site timezone.
    // The "timezone_name" variable is provided by DateAPI in Drupal 6.
    if (variable_get('configurable_timezones', 1) && $component['extra']['timezone'] == 'user') {
      $timezone_name = isset($GLOBALS['user']->timezone_name) ? $GLOBALS['user']->timezone_name : NULL;
    }
    else {
      $timezone_name = variable_get('date_default_timezone_name', NULL);
    }

    if (isset($timezone_name) && class_exists('DateTimeZone')) {
      $timezone = new DateTimeZone($timezone_name);
      $datetime = new DateTime($component['value'], $timezone);
      $default_values = webform_date_array($datetime->format('c'), 'time');
    }
    else {
      $default_values = webform_date_array(date('c', strtotime($component['value'])), 'time');
    }
  }
  else {
    $default_values = array(
      'hour' => '',
      'minute' => '',
      'second' => '',
    );
  }

  $first_hour = 0;
  $last_hour = 23;
  if ($component['extra']['hourformat'] == '12-hour') {
    $first_hour = 1;
    $last_hour = 12;
    $default_values = webform_time_convert($default_values, '12-hour');
    $default_values['ampm'] = $default_values['ampm'] ? $default_values['ampm'] : 'am';
  }

  // Generate the choices for drop-down selects.
  $hours[''] = t('hour');
  $minutes[''] = t('minute');
  for ($i = $first_hour; $i <= $last_hour; $i++) $hours[$i] = $i;
  for ($i = 0; $i <= 59; $i++) $minutes[$i] = $i < 10 ? "0$i" : $i;
  $ampms = array('am' => t('am'), 'pm' => t('pm'));

  $element = array(
    '#title' => $component['name'],
    '#required' => $component['mandatory'],
    '#weight' => $component['weight'],
    '#description' => _webform_filter_descriptions($component['extra']['description']),
    '#prefix' => '<div class="webform-component webform-component-' . $component['type'] . '" id="webform-component-' . $component['form_key'] . '">',
    '#suffix' => '</div>',
    '#theme' => 'webform_time',
    '#element_validate' => array('webform_validate_time'),
    '#hourformat' => $component['extra']['hourformat'],
    '#webform_component' => $component,
  );

  $element['hour'] = array(
    '#prefix' => '',
    '#type' => 'select',
    '#default_value' => $default_values['hour'],
    '#options' => $hours,
  );
  $element['minute'] = array(
    '#prefix' => ':',
    '#type' => 'select',
    '#default_value' => $default_values['minute'],
    '#options' => $minutes,
  );
  if ($component['extra']['hourformat'] == '12-hour') {
    $element['ampm'] = array(
      '#type' => 'radios',
      '#default_value' => $default_values['ampm'],
      '#options' => $ampms,
    );
  }

  if (isset($value[0]) && $value[0] !== '') {
    $value = webform_date_array($value[0], 'time');
    if ($component['extra']['hourformat'] == '12-hour') {
      $value = webform_time_convert($value, '12-hour');
    }

    $element['hour']['#default_value'] = $value['hour'];
    $element['minute']['#default_value'] = $value['minute'];
    if (isset($value['ampm'])) {
      $element['ampm']['#default_value'] = $value['ampm'];
    }
  }

  return $element;
}

/**
 * Theme a webform time element.
 */
function theme_webform_time($element) {
  // Add error classes to all items within the element.
  if (form_get_error($element)) {
    $element['hour']['#attributes']['class'] = 'error';
    $element['minute']['#attributes']['class'] = 'error';
  }

  $output = '<div class="container-inline">' . drupal_render($element['hour']) . drupal_render($element['minute']) . drupal_render($element['ampm']) . '</div>';

  $element['#type'] = 'element';
  return theme('form_element', $element, $output);
}

function webform_validate_time($element, $form_state) {
  $form_key = $element['#webform_component']['form_key'];
  $name = $element['#webform_component']['name'];

  // Check if the user filled the required fields.
  foreach ($element['#hourformat'] == '12-hour' ? array('hour', 'minute', 'ampm') : array('hour', 'minute') as $field_type) {
    if ($element[$field_type]['#value'] == '' && $element['#required']) {
      form_error($element, t('%field field is required.', array('%field' => $name)));
      return;
    }
  }

  // Check for a valid time.
  if ($element['hour']['#value'] !== '' || $element['minute']['#value'] !== '') {
    if (!is_numeric($element['hour']['#value']) || !is_numeric($element['minute']['#value']) || (isset($element['ampm']) && $element['ampm']['#value'] === '')) {
      form_error($element, t('Entered %name is not a valid time.', array('%name' => $name)));
      return;
    }
  }
}

/**
 * Implementation of _webform_submit_component().
 */
function _webform_submit_time($component, $value) {
  // Convert to 24-hour time before string conversion.
  if ($component['extra']['hourformat'] == '12-hour') {
    $value = webform_time_convert($value, '24-hour');
  }

  // Convert the value into a ISO 8601 string.
  return $value['hour'] !== '' ? webform_date_string($value, 'time') : '';
}

/**
 * Implementation of _webform_display_component().
 */
function _webform_display_time($component, $value, $format = 'html') {
  $value = webform_date_array(isset($value[0]) ? $value[0] : '', 'time');
  if ($component['extra']['hourformat'] == '12-hour') {
    $value = webform_time_convert($value, '12-hour');
  }

  return array(
    '#title' => $component['name'],
    '#weight' => $component['weight'],
    '#theme' => 'webform_display_time',
    '#theme_wrappers' => $format == 'html' ? array('webform_element') : array('webform_element_text'),
    '#post_render' => array('webform_element_wrapper'),
    '#component' => $component,
    '#format' => $format,
    '#hourformat' => $component['extra']['hourformat'],
    '#value' => $value,
  );
}

/**
 * Format the output of data for this component.
 */
function theme_webform_display_time($element) {
  $output = ' ';
  if (isset($element['#value']['hour']) && isset($element['#value']['minute'])) {
    if ($element['#hourformat'] == '24-hour') {
      $output = sprintf('%02d', $element['#value']['hour']) . ':' . sprintf('%02d', $element['#value']['minute']);
    }
    else {
      $output = $element['#value']['hour'] . ':' . sprintf('%02d', $element['#value']['minute']) . ' ' . $element['#value']['ampm'];
    }
  }
  return $output;
}

/**
 * Implementation of _webform_analysis_component().
 */
function _webform_analysis_time($component, $sids = array()) {
  $placeholders = count($sids) ? array_fill(0, count($sids), "'%s'") : array();
  $sidfilter = count($sids) ? " AND sid in (" . implode(",", $placeholders) . ")" : "";
  $query = 'SELECT no,data ' .
    ' FROM {webform_submitted_data} ' .
    ' WHERE nid = %d ' .
    ' AND  cid = %d ' . $sidfilter .
    ' ORDER BY sid ASC ';

  $result = db_query($query, array_merge(array($component['nid'], $component['cid']), $sids));

  $times = array();
  $submissions = 0;
  while ($row = db_fetch_array($result)) {
    $submissions++;
    if ($row['data']) {
      $times[] = webform_date_array($row['data']);
    }
  }

  // Display stats.
  $nonblanks = count($times);
  $rows[0] = array(t('Left Blank'), ($submissions - $nonblanks));
  $rows[1] = array(t('User entered value'), $nonblanks);
  return $rows;
}

/**
 * Implementation of _webform_table_component().
 */
function _webform_table_time($component, $value) {
  if ($value[0]) {
    $time = webform_date_array($value[0], 'time');
    if ($component['extra']['hourformat'] == '24-hour') {
      return sprintf('%02d', $time['hour']) . ':' . sprintf('%02d', $time['minute']);
    }
    else {
      $time = webform_time_convert($time, '12-hour');
      return $time['hour'] . ':' . sprintf('%02d', $time['minute']) . ' ' . $time['ampm'];
    }
  }
  else {
    return '';
  }
}

/**
 * Implementation of _webform_csv_headers_component().
 */
function _webform_csv_headers_time($component, $export_options) {
  $header = array();
  $header[0] = '';
  $header[1] = '';
  $header[2] = $component['name'];
  return $header;
}

/**
 * Implementation of _webform_csv_data_component().
 */
function _webform_csv_data_time($component, $export_options, $value) {
  if ($value[0]) {
    $time = webform_date_array($value[0], 'time');
    if ($component['extra']['hourformat'] == '24-hour') {
      return sprintf('%02d', $time['hour']) . ':' . sprintf('%02d', $time['minute']);
    }
    else {
      $time = webform_time_convert($time, '12-hour');
      return $time['hour'] . ':' . sprintf('%02d', $time['minute']) . ' ' . $time['ampm'];
    }
  }
  else {
    return '';
  }
}

/**
 * Convert a time between a 24-hour and a 12-hour value.
 *
 * @param $array
 *   An array of hour, minute, second, and optionally ampm.
 * @param $format
 *   Either 12-hour or 24-hour.
 * @return
 *   An array with hour, minute, second, and ampm (if using "12-hour").
 */
function webform_time_convert($array, $format) {
  if ($array['hour'] !== '') {
    if ($format == '12-hour') {
      $array['ampm'] = ($array['hour'] >= 12 && $array['hour'] < 24) ? 'pm' : 'am';
      $array['hour'] = ($array['hour'] > 12 || $array['hour'] == 0) ? abs($array['hour'] - 12) : (int) $array['hour'];
    }
    elseif ($format == '24-hour' && isset($array['ampm'])) {
      $array['hour'] = ($array['hour'] < 12 && $array['ampm'] == 'pm') ? $array['hour'] + 12 : (int) $array['hour'];
    }
  }

  if ($format == '12-hour' && !isset($array['ampm'])) {
    $array['ampm'] = '';
  }
  elseif ($format == '24-hour' && isset($array['ampm'])) {
    unset($array['ampm']);
  }

  return $array;
}