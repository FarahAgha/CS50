<?php

    //configuration
    require("../includes/config.php");
    
    //if redirected from form
    if( $_SERVER["REQUEST_METHOD"] =="POST")
    {
        //check for blank cash field
        if(empty($_POST["cash"]))
        {
            apologize("You must enter amount.");
        }
        
        //chk for -ve cash value
        if($_POST["cash"] <= 0)
        {
            apologize("Invalid amount.");
        }
        
        //insert the cash amount
        $cash = $_POST["cash"];
        query("UPDATE `users` SET `Cash` = `Cash` + $cash WHERE `id` = ?", $_SESSION['id']);
        
        //back to index page
        redirect("/");
        
    }
    else
    {
        
        
        //display form
        render("addcash_form.php", [ "title"=>"Deposite Additional Fund"]);
    }
?>


