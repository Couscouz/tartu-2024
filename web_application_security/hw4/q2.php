<?php
//headers
header('Access-Control-Allow-Origin: https://webappsec.cs.ut.ee');
header('Access-Control-Allow-Credentials: true');
header('Content-Type: application/json');

//Check if the method is POST
if ($_SERVER['REQUEST_METHOD'] === "POST") {
    header('Vary: Origin');
    //Get the JSON data from post body
    $json_data = file_get_contents('php://input');
    //Decode timestamp
    $data = json_decode($json_data, true);
    //Check if timestamp key exists in the data
    if (isset($data['timestamp'])) {
        //Get the timestamp value from the data
        $timestamp = $data['timestamp'];
        //Convert the timestamp to a weekday
        $weekday = date('l', $timestamp);
        //Send JSON response
        echo json_encode(array('weekday' => $weekday));
    } else {
        //Invalid request - timestamp key is missing
        http_response_code(400);
        echo json_encode(array('error' => 'Invalid timestamp'));
    }
} else if ($_SERVER['REQUEST_METHOD'] === "OPTIONS") {
    //Preflight request
    header('Access-Control-Allow-Methods: POST,OPTIONS');
    header('Access-Control-Allow-Headers: Content-Type, Authorization');
} else {
    //Invalid request method
    http_response_code(405);
    echo json_encode(array('error' => 'This method is not handled'));
}
?>