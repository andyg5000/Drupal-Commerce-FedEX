<?php

/**
 * @file
 * Admin functions for Commerce FedEx.
 */

/**
 * Form builder function for module settings.
 *
 * @return string
 *   Drupal form for USPS settings
 */
function commerce_fedex_settings_form() {
  $form = array();
  $form['auth'] = array(
    '#title' => t('FedEx web authentication'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
  );
  $form['auth']['commerce_fedex_key'] = array(
    '#type' => 'textfield',
    '#title' => t('FedEx Key'),
    '#default_value' => variable_get('commerce_fedex_key'),
  );
  $form['auth']['commerce_fedex_password'] = array(
    '#type' => 'password',
    '#title' => t('FedEx Password'),
    '#description' => t('If you don\'t want to change saved password, leave it blank'),
  );
  $form['client'] = array(
    '#title' => t('FedEx client account'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
  );
  $form['client']['commerce_fedex_account_number'] = array(
    '#type' => 'textfield',
    '#title' => t('FedEx Account Number'),
    '#default_value' => variable_get('commerce_fedex_account_number'),
  );
  $form['client']['commerce_fedex_meter_number'] = array(
    '#type' => 'textfield',
    '#title' => t('FedEx Meter Number'),
    '#default_value' => variable_get('commerce_fedex_meter_number'),
  );
  $form['origin'] = array(
    '#title' => t('Ship from location'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
  );
  $form['origin'] = array(
    '#type' => 'fieldset',
    '#title' => t('Ship From Address'),
    '#collapsible' => TRUE,
  );
  $form['origin']['commerce_fedex_company_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Company Name'),
    '#default_value' => variable_get('commerce_fedex_company_name')
  );
  $form['origin']['commerce_fedex_address_line_1'] = array(
    '#type' => 'textfield',
    '#title' => t('Address'),
    '#default_value' => variable_get('commerce_fedex_address_line_1')
  );
  $form['origin']['commerce_fedex_address_line_2'] = array(
    '#type' => 'textfield',
    '#title' => t('Address (Additional)'),
    '#default_value' => variable_get('commerce_fedex_address_line_2')
  );
  $form['origin']['commerce_fedex_city'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
    '#default_value' => variable_get('commerce_fedex_city')
  );
  $form['origin']['commerce_fedex_state'] = array(
    '#type' => 'select',
    '#title' => t('State'),
    '#default_value' => variable_get('commerce_fedex_state'),
    '#options' => array(
      '' => t('Please Select'),
      'AL' => t('Alabama'),
      'AK' => t('Alaska'),
      'AZ' => t('Arizona'),
      'AR' => t('Arkansas'),
      'CA' => t('California'),
      'CO' => t('Colorado'),
      'CT' => t('Connecticut'),
      'DE' => t('Delaware'),
      'DC' => t('District of Columbia'),
      'FL' => t('Florida'),
      'GA' => t('Georgia'),
      'HI' => t('Hawaii'),
      'ID' => t('Idaho'),
      'IL' => t('Illinois'),
      'IN' => t('Indiana'),
      'IA' => t('Iowa'),
      'KS' => t('Kansas'),
      'KY' => t('Kentucky'),
      'LA' => t('Louisiana'),
      'ME' => t('Maine'),
      'MD' => t('Maryland'),
      'MA' => t('Massachusetts'),
      'MI' => t('Michigan'),
      'MN' => t('Minnesota'),
      'MS' => t('Mississippi'),
      'MO' => t('Missouri'),
      'MY' => t('Montana'),
      'NE' => t('Nebraska'),
      'NV' => t('Nevada'),
      'NH' => t('New Hampshire'),
      'NJ' => t('New Jersey'),
      'NM' => t('New Mexico'),
      'NY' => t('New York'),
      'NC' => t('North Carolina'),
      'ND' => t('North Dakota'),
      'OH' => t('Ohio'),
      'OK' => t('Oklahoma'),
      'OR' => t('Oregon'),
      'PA' => t('Pennsylvania'),
      'RI' => t('Rhode Island'),
      'SC' => t('South Carolina'),
      'SD' => t('South Dakota'),
      'TN' => t('Tennessee'),
      'TX' => t('Texas'),
      'UT' => t('Utah'),
      'VT' => t('Vermont'),
      'VA' => t('Virginia'),
      'WA' => t('Washington'),
      'WV' => t('West Virginia'),
      'WI' => t('Wisconsin'),
      'WY' => t('Wyoming'),
    )
  );
  $form['origin']['commerce_fedex_postal_code'] = array(
    '#type' => 'textfield',
    '#title' => t('Postal Code'),
    '#size' => 5,
    '#default_value' => variable_get('commerce_fedex_postal_code')
  );
  $form['origin']['commerce_fedex_country_code'] = array(
    '#type' => 'select',
    '#title' => t('Country'),
    '#default_value' => variable_get('commerce_fedex_country_code'),
    '#options' => array(
      '' => t('Please Select'),
      'US' => t('United States of America'),
    )
  );
  $form['services'] = array(
    '#type' => 'fieldset',
    '#title' => t('Enabled FedEx Shipping Services'),
    '#collapsible' => TRUE,
  );
  $form['services']['commerce_fedex_services'] = array(
    '#type' => 'checkboxes',
    '#options' => commerce_fedex_shipping_service_types(),
    '#default_value' => variable_get('commerce_fedex_services', array())
  );
  $form['packaging'] = array(
    '#type' => 'fieldset',
    '#title' => t('FedEx Packaging'),
    '#collapsible' => TRUE,
  );
  $form['packaging']['commerce_fedex_default_package_type'] = array(
    '#type' => 'select',
    '#title' => t('Default package type'),
    '#options' => commerce_fedex_package_types(),
    '#defailt_value' => variable_get('commerce_fedex_default_package_type'),
  );
  $form['packaging']['default_package_size'] = array(
    '#type' => 'fieldset',
    '#title' => t('Default package size (inches)'),
    '#collapsible' => FALSE,
    '#description' => 'FedEx requires a package size when determining estimates.',
  );
  $form['packaging']['default_package_size']['commerce_fedex_default_package_size_length'] = array(
    '#type' => 'textfield',
    '#title' => t('Length'),
    '#size' => 5,
    '#required' => TRUE,
    '#default_value' => variable_get('commerce_fedex_default_package_size_length'),
  );
  $form['packaging']['default_package_size']['commerce_fedex_default_package_size_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Width'),
    '#size' => 5,
    '#required' => TRUE,
    '#default_value' => variable_get('commerce_fedex_default_package_size_width'),
  );
  $form['packaging']['default_package_size']['commerce_fedex_default_package_size_height'] = array(
    '#type' => 'textfield',
    '#title' => t('Height'),
    '#size' => 5,
    '#required' => TRUE,
    '#default_value' => variable_get('commerce_fedex_default_package_size_height'),
  );
  $form['packaging']['default_package_size']['details'] = array(
    '#markup' => 'The package size is used to determine the number of packages necessary to
      create a FedEx shipping cost estimate. <strong>If products do not have physical dimensions and
      weights associated with them, the estimates will not be accurate.</strong> The logic implemented works as:
      <ul>
      <li>Assume each order requires at least one package.</li>
      <li>Use the combined volume of all products in an order to determine the number of packages.</li>
      </ul>
      This is a simple calculation that can get close to actual shipping costs. More
      complex logic involving multiple package sizes, weights, and void space can be implemented via
      custom modules.',
  );
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  return $form;
}

/*
 * Implements hook_form_validate().
 */

function commerce_fedex_settings_form_validate($form, $form_state) {

}

/*
 * Implements hook_form_submit().
 */

function commerce_fedex_settings_form_submit($form, $form_state) {
  // Loop through each of the settings fields and save their values.
  foreach (commerce_fedex_settings_fields() as $key) {
    if (!empty($form_state['values'][$key])) {
      $value = $form_state['values'][$key];
      variable_set($key, $value);
    }
  }
  drupal_set_message(t('The FedEx configuration options have been saved.'));
}