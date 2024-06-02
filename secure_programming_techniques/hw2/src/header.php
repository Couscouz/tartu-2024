<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>SecProg HW2</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-QWTKZyjpPEjISv5WaRU9OFeRpok6YctnYmDr5pNlyT2bRjXh0JMhjY6hW+ALEwIH" crossorigin="anonymous">
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap-icons@1.11.3/font/bootstrap-icons.min.css">
  </head>
  <body>

  <nav class="navbar navbar-expand-lg navbar-light bg-light">
        <div class="container-fluid">
            <a class="navbar-brand" href="/">SecProg HW2</a>
            <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarNav" aria-controls="navbarNav" aria-expanded="false" aria-label="Toggle navigation">
                <span class="navbar-toggler-icon"></span>
            </button>
            <div class="collapse navbar-collapse" id="navbarNav">
                <ul class="navbar-nav">
                    <li class="nav-item">
                        <a class="nav-link" href="/index.php">Posts</a>
                    </li>
                    <?php
                        include_once('access_control.php');

                        // only for admin users
                        if (admin($_SESSION)) {
                            echo "<li class=\"nav-item\"><a class=\"nav-link\" href=\"/create.php\">Create</a></li>";
                            echo "<li class=\"nav-item\"><a class=\"nav-link\" href=\"/profile.php\">Profile</a></li>";
                            echo "<li class=\"nav-item\"><a class=\"nav-link\" href=\"/access.php\">Access</a></li>";
                        }
                        // for all users
                        if (user($_SESSION)) {
                            echo "<li class=\"nav-item\"><a class=\"nav-link\" href=\"/report.php\">Report</a></li>";
                            echo "<li class=\"nav-item\"><a class=\"nav-link\" href=\"/logout.php\">Log out</a></li>";
                        } else{
                            echo "<li class=\"nav-item\"><a class=\"nav-link\" href=\"/login.php\">Login</a></li>";
                        }
                    ?>
                </ul>
            </div>
        </div>
    </nav>

    <div class="container my-5 text-center">