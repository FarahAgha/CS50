<?php

    // configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        //user name isnt blank else apologize
        if($_POST['username']== '')
        {
            apologize("User name cannot be empty");
            
        } //password arent blank else apologize ("Password is blank")
        else if($_POST['password'] == '' )
        {
            apologize("Password cannot be empty");
            
        } //password should be same else apologize ("Password mismatch")
        else if ($_POST['password'] != $_POST['confirmation'])
        {
            apologize("Password Mismatch");
            
        }
        
        // insert user into database
        if(QUERY("INSERT INTO users (USERNAME ,HASH, CASH) VALUES(?, ?, 999.9999)", $_POST['username'], CRYPT($_POST['password'])) === false)
        {
            //if insertion query returns false === then user not created 
            apologize("Duplicate User Names"); 
        }
        else{
            
            $rows = query("SELECT LAST_INSERT_ID() AS id");
            $id = $rows[0]["id"];
            $_SESSION["id"] = $id;
            redirect("/");
        }
    }
    else
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

?>
