var d = document,
    itemBox = d.querySelectorAll('.item_box'); // блок каждого товара

// Функция кроссбраузерная установка обработчика событий
function addEvent(elem, type, handler){
  if(elem.addEventListener){
    elem.addEventListener(type, handler, false);
  } else {
    elem.attachEvent('on'+type, function(){ handler.call( elem ); });
  }
  return false;
}

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

function send_book_on_add(_id, _author, _title, _price) {
	$.ajax({
		url: '/add_book',
		dataType: 'json',
		type: 'POST',
		cache: 'false',
		contentType: 'application/json',
		data: JSON.stringify({
			id: _id,
			author: _author,
			title: _title,
			price: _price
		}),
		success: function() {
			showBooks()
		}
	})
}

// Записываем данные в LocalStorage
function setCartData(_id, _author, _title, _price){
	$.ajax({
		url: '/add_book',
		dataType: 'json',
		type: 'POST',
		cache: 'false',
		contentType: 'application/json',
		data: JSON.stringify({
			id: _id,
			author: _author,
			title: _title,
			price: _price
		}),
		success: function() {
			showBooks()
		}
	})
	return false;
}
// Добавляем товар в корзину
function addToCart(e){
	this.disabled = true; // блокируем кнопку на время операции с корзиной
	var parentBox = this.parentNode, // родительский элемент кнопки &quot;Добавить в корзину&quot;
		itemId = this.getAttribute('data-id'), // ID товара
		itemAuthor = parentBox.querySelector('.author').innerHTML, // название товара
		itemTitle = parentBox.querySelector('.item_title').innerHTML, // название товара
		itemPrice = parentBox.querySelector('.item_price').innerHTML; // стоимость товара
	//** если товара в корзине еще нет, то добавляем в объект

	if(!setCartData(itemId, itemAuthor, itemTitle, itemPrice)){
		this.disabled = false; // разблокируем кнопку после обновления LS
	}
	return false;
}

// Устанавливаем обработчик события на каждую кнопку &quot;Добавить в корзину&quot;
for(var i = 0; i < itemBox.length; i++){
	addEvent(itemBox[i].querySelector('.add_item'), 'click', addToCart);
}

