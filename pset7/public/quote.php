<?php

    // configuration
    require("../includes/config.php"); 

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate symbol
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide symbol.");
        }
        
        // get the post symbol
        $stock = lookup($_POST["symbol"]);
        
        if($stock === false)
        {
            apologize("Inappropriate symbol.");
        }
        
        //format the number to display 2 decimal places
        $formatted_number = number_format((float)$stock["price"], 2, '.', '');
        
        //store all the associated information into an array
        $values = array(
            ["name" =>  $stock["name"],   
            "symbol" => $stock["symbol"],   
            "price" => $formatted_number]);
        
        //redirect to display information
        render("quote_view.php", ["values" => $values, "title" => "Get Quote" ]);
        
    }
    else
    {
        //redirect to display form
        render("quote_form.php", ["title" => "Quote" ]);
    }

?>
