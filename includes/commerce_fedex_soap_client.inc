<?php

function commerce_fedex_create_soap_request($order) {
  ini_set('soap.wsdl_cache_enabled', '0');
  $wsdl = drupal_get_path('module', 'commerce_fedex') . '/includes/RateService_v10.wsdl';
  $client = new SoapClient($wsdl, array('trace' => 1)); // Refer to http://us3.php.net/manual/en/ref.soap.php for more information

  $request['WebAuthenticationDetail'] = array(
    'UserCredential' => array(
      'Key' => variable_get('commerce_fedex_key', NULL),
      'Password' => variable_get('commerce_fedex_password', NULL)
    )
  );
  $request['ClientDetail'] = array(
    'AccountNumber' => variable_get('commerce_fedex_account_number', NULL),
    'MeterNumber' => variable_get('commerce_fedex_meter_number', NULL)
  );
  $request['TransactionDetail'] = array('CustomerTransactionId' => ' *** Rate Request v10 using PHP ***');
  $request['Version'] = array(
    'ServiceId' => 'crs',
    'Major' => '10',
    'Intermediate' => '0',
    'Minor' => '0'
  );
  $request['ReturnTransitAndCommit'] = true;
  $request['RequestedShipment']['DropoffType'] = 'REGULAR_PICKUP'; // valid values REGULAR_PICKUP, REQUEST_COURIER, ...
  $request['RequestedShipment']['ShipTimestamp'] = date('c');
  $request['RequestedShipment']['ServiceType'] = 'FEDEX_GROUND'; // valid values STANDARD_OVERNIGHT, PRIORITY_OVERNIGHT, FEDEX_GROUND, ...
  $request['RequestedShipment']['PackagingType'] = 'YOUR_PACKAGING'; // valid values FEDEX_BOX, FEDEX_PAK, FEDEX_TUBE, YOUR_PACKAGING, ...
  $request['RequestedShipment']['TotalInsuredValue'] = array('Ammount' => 100, 'Currency' => 'USD');
  $request['RequestedShipment']['Shipper'] = addShipper();
  $request['RequestedShipment']['Recipient'] = addRecipient();
  $request['RequestedShipment']['RateRequestTypes'] = 'ACCOUNT';
  $request['RequestedShipment']['RateRequestTypes'] = 'LIST';
  $request['RequestedShipment']['PackageCount'] = '1';
  $request['RequestedShipment']['RequestedPackageLineItems'] = addPackageLineItem1();
  try {
    $response = $client ->getRates($request);
    dpm($response);
  } catch (SoapFault $exception) {
    drupal_set_message($exception . ' ' . $client);
  }
}

function addShipper() {
  $shipper = array(
    'Contact' => array(
      'PersonName' => 'Sender Name',
      'CompanyName' => 'Sender Company Name',
      'PhoneNumber' => '9012638716'),
    'Address' => array(
      'StreetLines' => array('Address Line 1'),
      'City' => 'Austin',
      'StateOrProvinceCode' => 'TX',
      'PostalCode' => '73301',
      'CountryCode' => 'US')
  );
  return $shipper;
}

function addRecipient() {
  $recipient = array(
    'Contact' => array(
      'PersonName' => 'Recipient Name',
      'CompanyName' => 'Company Name',
      'PhoneNumber' => '9012637906'
    ),
    'Address' => array(
      'StreetLines' => array('Address Line 1'),
      'City' => 'Richmond',
      'StateOrProvinceCode' => 'BC',
      'PostalCode' => 'V7C4V4',
      'CountryCode' => 'CA',
      'Residential' => false)
  );
  return $recipient;
}

function addPackageLineItem1() {
  $packageLineItem = array(
    'SequenceNumber' => 1,
    'GroupPackageCount' => 1,
    'Weight' => array(
      'Value' => 50.0,
      'Units' => 'LB'
    ),
    'Dimensions' => array(
      'Length' => 108,
      'Width' => 5,
      'Height' => 5,
      'Units' => 'IN'
    )
  );
  return $packageLineItem;
}

function setEndpoint($var) {
  if ($var == 'changeEndpoint')
    Return false;
  if ($var == 'endpoint')
    Return '';
}