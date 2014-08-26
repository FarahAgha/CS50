
<form action="sell.php" method="post">
    <fieldset>
        <div class="form-group">
            <select class="form-control" name="symbol">
                <option value=""> </option>
                <?php foreach ($position as $rows): ?>
                    <option 
                        value=  
                        <?= $rows["symbol"] ?>
                    >
                        <?= $rows["symbol"] ?>
                    </option>
                <?php endforeach ?>          
            </select>
        </div>
        <div class="form-group">
            <input type="text" name = "num_of_shares">
            <button type="submit" class="btn btn-default">Sell</button>
        </div>
    </fieldset>
</form>

