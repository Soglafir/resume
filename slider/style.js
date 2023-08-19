//кнопка next 
var button_next = document.getElementById('__next');
//кнопка prev 
var button_prev = document.getElementById('__prev');
//обертка для всех item 
var newblockcase = document.getElementsByClassName('wrapper__slider');
//ширина всего слайдера
var newblockcase_width = parseFloat(getComputedStyle(newblockcase[0]).width);
//все item в слайдере 
var block_slider = document.getElementsByClassName('__item');
//ширина одного item
var width = parseFloat(getComputedStyle(block_slider[0]).width);
//внешний левый отступ одного из item (т.к. нам нужно учитывать еще и правый отступ левый умножается на 2)
var margin = parseFloat(getComputedStyle(block_slider[0]).marginLeft)*2;
//рамка item по левой границе 
var border = parseFloat(block_slider[0].clientLeft);
//переменная исп. для отслеживания текущей позиции 
var x = 0.00;
//переменная отслеживает кол-во сдвинутых блоков 
var cl_item = 0;
//количество отображаемых item  
var show_slider = parseInt(newblockcase_width/width);
//событие клика на кнопку next
button_next.onclick = function(){
	if(cl_item < block_slider.length - show_slider){
		x = x - width - margin - border*2;
		for(let i = 0; i < block_slider.length; i++){
			block_slider[i].style.left = x + 'px';
		}
		++cl_item;
	}	
}
//событие клика на кнопку prev
button_prev.onclick = function(){
	if(cl_item > 0){
		x = x + width + margin + border*2;
		for(let i = 0; i < block_slider.length; i++){
			block_slider[i].style.left = x + 'px';
		}			
		--cl_item;
	}
}
