function showBooks() {
    $.get('get', function(data) {
        let table = "<table border='1'><tr><th>Id</th><th>Title</th>" +
            "<th>Author</th><th>Price</th><tr>";

        for (i = 0; i < data.length; ++i) {
            table = table + "<tr><td>" + data[i].id + "</td><td>" +
                data[i].author  + "</td><td>" + data[i].title + "</td><td>" +
                data[i].price + "</td></tr>";
        }
        table = table + "</table>";


        $("#cart_content").html(table);
    });
}

/*
function showBooks() {
    $.get('get', function(data) {
        let table = "<table class='shopping_list' border='1'><tr><th>Id</th><th>Title</th>" +
            "<th>Author</th><th>Price</th><tr>";

        if (data.length == 0) {
            var totalCount = data.length,
                totalSum = 0;
            for (i = 0; i < data.length; ++i) {
                table = table + "<tr><td>" + data[i].id + "</td><td>" +
                    data[i].author  + "</td><td>" + data[i].title + "</td><td>" +
                    data[i].price + "</td></tr>";
                totalSum += data[i].price;
            }
            table += '<tr><td><strong>Итого</strong></td>' +
                '<td><span id="total_sum">'+ totalSum +'</span> $</td>' +
                '<td><span id="total_count">'+ totalCount +'</span> шт.</td></tr>';
            table += '<table>';

            $("#cart_content").html(table);
        } else {
            // если в корзине пусто, то сигнализируем об этом
            $("#cart_content").html('В корзине пусто!');
        }
    });
}
 */
function add_book() {
    $.ajax({
        url: '/add_book',
        dataType: 'json',
        type: 'POST',
        cache: 'false',
        contentType: 'application/json',
        data: JSON.stringify({
            id: $("#book_id").val(),
            author: $("#book_author").val(),
            title: $("#book_title").val(),
            price: $("#book_price").val()
        }),
        success: function() {
            showBooks()
        }
    })
}

function del_book() {
    $.ajax({
        url: '/del_book',
        dataType: 'json',
        type: 'POST',
        cache: 'false',
        contentType: 'application/json',
        data: JSON.stringify({
            id: $("#book_id").val()
        }),
        success: function() {
            showBooks()
        }
    })
}

function del_all_book() {
    $.ajax({
        url: '/del_all_book',
        dataType: 'json',
        type: 'POST',
        cache: 'false',
        contentType: 'application/json',
        data: JSON.stringify({}),
        success: function() {
            showBooks()
        }
    })
}

$(document).ready(function() {
    showBooks()
});