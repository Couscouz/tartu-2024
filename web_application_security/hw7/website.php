<!DOCTYPE html>
<html>
<head>
    <title>My Personal Page</title>
</head>
<body>
    <a href="?page=home.html">Home</a>
    <a href="?page=about.html">About</a>
    <a href="?page=cats.html">Cat Pictures</a>
    <hr/>

    <?php
    // List of allowed pages
    $allowedPages = ['home.html', 'about.html', 'cats.html'];

    // Check if the page parameter is set and if it's in the allowed list
    if (isset($_GET['page']) && in_array($_GET['page'], $allowedPages)) {
        include('includes/'.$_GET['page']);
    } else {
        include('includes/home.html'); // Default to home page if page is not specified or not allowed
    }
    ?>

    <hr/>

</body>
</html>
