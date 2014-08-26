<table class="table table-striped">

    <thead >
        <tr>
            <th>Transaction</th>
            <th>Date/Time</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price</th>
        </tr>
    </thead>

    <tbody align="left">
        <!-- display shares info stored in an array (row) -->
        <?php  
            
            foreach ($history as $position):  ?> 
            <tr>
                <td><?= $position["transaction"] ?></td>
                <td><?= $position["dateTime"] ?></td>
                <td><?= $position["symbol"] ?></td>
                <td><?= $position["shares"] ?></td>
                <? $formatted_number = number_format((float)$position["price"], 2, '.', ''); ?>
                <td><?= $formatted_number ?></td>
            </tr>        
        <?php endforeach ?>
        
    <tbody>
</table>
<div>
 <a href = "http://pset7/" >Home</a> 
</div>
