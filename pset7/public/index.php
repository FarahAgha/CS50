<?php

    // configuration
    require("../includes/config.php"); 

    //collect share information from "portfolio" table store in an array (e.g. row)
    $sql_shares = query("SELECT * FROM `portfolios` WHERE `id` = ?",  $_SESSION['id']);
    
    // share information to pass to portfolios
    $positions = [];
    foreach ($sql_shares as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                
                "symbol" => $row["symbol"],
                "name" => $stock["name"],
                "shares" => $row["shares"],
                "price" => number_format((float)$stock["price"], 2, '.', '')
            ];
        }
    }
    
    //collect cash info from "user"  
    $sql_cash = query("SELECT * FROM `users` WHERE `id` = ?",  $_SESSION['id']);
    $cash = number_format((float)$sql_cash[0]["Cash"], 2, '.', '');
    
    // render portfolio
    render("portfolio.php", ["cash" => $cash, "positions" => $positions, "title" => "Portfolio"]);
    
?>
