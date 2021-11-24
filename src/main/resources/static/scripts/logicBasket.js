var d = document,
	cartCont = d.getElementById('cart_content');// блок вывода данных корзины

// Функция кроссбраузерная установка обработчика событий
function addEvent(elem, type, handler){
    if(elem.addEventListener){
        elem.addEventListener(type, handler, false);
    } else {
        elem.attachEvent('on'+type, function(){ handler.call( elem ); });
    }
    return false;
}

// Открываем корзину со списком добавленных товаров
function openCart(e){
	$.get('get', function(data) {
		let table = "<table class='shopping_list' border='1'><tr><th>Id</th><th>Title</th>" +
			"<th>Author</th><th>Price</th><tr>";

		if (data.length > 0) {
			var totalCount = data.length,
				totalSum = 0;
			for (i = 0; i < data.length; ++i) {
				table = table + "<tr><td>" + data[i].id +
					"</td><td>" +
					data[i].author  + "</td><td>" + data[i].title + "</td><td>" +
					data[i].price + "</td>";

				totalSum += data[i].price;
			}
			table += '<tr><td><strong>Итого</strong></td>' +
				'<td></td>' +
				'<td><span id="total_count">'+ totalCount +'</span>шт.</td>' +
				'<td><span id="total_sum">'+ totalSum +'</span>$</td></tr>';
			table += '<table>';

			$("#cart_content").html(table);
		} else {
			// если в корзине пусто, то сигнализируем об этом
			$("#cart_content").html('В корзине пусто!');
		}
	});
	return false;
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


/* Открыть корзину */
addEvent(d.getElementById('checkout'), 'click', openCart);
/* Удаление из корзины */
addEvent(d.body, 'click', del_book, false);
/* Очистить корзину */
addEvent(d.getElementById('clear_cart'), 'click', del_all_book);
addEvent(d.getElementById('del_book'), 'click', del_book);