<?php
    
    //configuration
    require("../includes/config.php");
    
    //get history of the current users profile
    $sql_history = query("SELECT * FROM `history` WHERE `id` = ?", $_SESSION['id']);
    
    //redirect the form to display history
    render("history_form.php", ["history" => $sql_history, "title" => "History"]);
?>
