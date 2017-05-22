
function $(sel){
	return document.querySelector(sel);
}
function $s(sel) {
    return document.querySelectorAll(sel);
}


var options = ["Starch", "Fruit", "Milk", "Vegetables", "Meat", "Fat"];
var body = $("body");
var servings = [];
var calories = [80, 60, 100, 35, 45, 45];
var total_calories = 0;

//Creates six selects for the user to choose number of servings for each serving type.
$("#new_week_button").addEventListener("click", function(){

	
	body.innerHTML = "<h1>Personal Meal Planner</h1>How many servings per day? <br><br>";
	
	var selector = document.createElement("div");
	
	for (var i = 0; i < options.length; ++i){
		var item = selector.appendChild(document.createElement("div"));
		var input_box = document.createElement("select");
		input_box.id = options[i] + "_input_box";
		for (var j = 0; j <= 15; ++j){
			var value = document.createElement("option");
			value.value = j;
			value.innerHTML = j;
			input_box.appendChild(value);

		}
		item.appendChild(input_box);
		item.appendChild(document.createTextNode("servings of " + options[i]));
		body.appendChild(selector);
	}

	var inputs = $s("select");

	for(var i = 0; i < options.length; ++i){
		inputs[i].type = "number";
		inputs[i].min = "0";
		inputs[i].max = "15";
		inputs[i].value = "0";
		inputs[i].id = "serv_select";
	}
	
	var go_button = document.createElement("button");
	go_button.innerHTML = "Create Chart";
	go_button.id = "go_button";
	body.appendChild(go_button);
	
	
	$("#go_button").addEventListener("click", function(){
		
		localStorage.clear();

		//creates 3 dimensional array for storing serving data. values: -1 is no serving, 0 is uneaten,
			//1 is eaten.
		for(var h = 0; h < 7; ++h){
			servings[h] = [];
			for(var i = 0; i < 6; ++i){
				servings[h][i] = [];
				for(var j = 0; j < 15; ++j){
					if (inputs[i].value > j){
						servings[h][i][j] = 0;
					}
					else{
						servings[h][i][j] = -1;
					}
				}
			}
		}
		
		create_chart();

	}, false);

	var back_button = document.createElement("button");
	back_button.innerHTML = "Go Back";
	back_button.id = "back_button";
	body.appendChild(back_button);
	
	
	$("#back_button").addEventListener("click", function(){
		location.reload();
	},false)

},false);


$("#load_week_button").addEventListener("click", function(){

	input = localStorage.getItem("servings");
		
	//loads local storage string and parses as 3d array.	
	if (input){
	
		temp_servings = JSON.parse("[" + input + "]");
		
		for(var h = 0; h < 7; ++h){
			servings[h] = [];
			for(var i = 0; i < 6; ++i){
				servings[h][i] = [];
				for(var j = 0; j < 15; ++j){
					servings[h][i][j] = temp_servings[(90 * h) + (15 * i) + j];
				}
			}
		}
		create_chart();
	}
	else{
		alert("Problem loading data. Please start a new week.");
	}




},false);


function create_chart(){

	body.innerHTML = "<h1>Personal Meal Planner</h1>"
	
	day_select = document.createElement("select");
	day_select.id = "day_select";
	var day = ["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"];
	for (var i = 0; i < 7; ++i){
		var new_day = document.createElement("option");
		new_day.value = i;
		new_day.innerHTML = day[i];
		day_select.appendChild(new_day);

	}
	
	day_select.addEventListener("change", draw_chart, false);
	
	body.appendChild(day_select);
	
	total_calories_box = document.createElement("div");
	total_calories_box.appendChild(document.createTextNode("Total calories consumed today: "));
	daily_calories = document.createElement("span");
	daily_calories.id = "daily_calories";
	total_calories_box.appendChild(daily_calories);
	total_calories_box.id="total_calories_box";
	body.appendChild(total_calories_box);
	
	draw_chart();
	
	var back_button = document.createElement("button");
	back_button.innerHTML = "Go Back";
	back_button.id = "back_button";
	body.appendChild(back_button);
	
	
	$("#back_button").addEventListener("click", function(){
		location.reload();
	},false);
	
}

//draws chart each time the day is changed or page is loaded
function draw_chart(){

	var existing_table = $("table");
	if (existing_table){
		body.removeChild(existing_table);
	}
	
	total_calories = 0;
	var table = document.createElement("table");
	var title_row = document.createElement("tr");
	title_row.id = "title_row";
	
	var servings_th = document.createElement("th");
	servings_th.appendChild(document.createTextNode("Serving"));
	title_row.appendChild(servings_th);
	
	var calories_th = document.createElement("th");
	calories_th.appendChild(document.createTextNode("kcal"));
	title_row.appendChild(calories_th);

	var servings_number = 15;
	for(var i = 0; i < 15; ++i){
		var count = 0;
		for(var h = 0; h < 6; ++h){
			count += servings[0][h][i];
		}
		if (count == -6){
			--servings_number;
		}
	
	}
	
	for (var i = 1; i <= servings_number; ++i){
		number_th = document.createElement("th");
		number_th.appendChild(document.createTextNode(i));
		title_row.appendChild(number_th);
	}
	
	table.appendChild(title_row);

	day = $("#day_select").value;
	
	for(var i = 0; i < 6; ++i){		
		
		var new_row = document.createElement("tr");
		
		var name_td = document.createElement("td");
		name_td.appendChild(document.createTextNode(options[i]));
		new_row.appendChild(name_td);
		
		var calories_td = document.createElement("td");
		calories_td.appendChild(document.createTextNode(calories[i]));
		new_row.appendChild(calories_td);
		
			for(var j = 0; j < servings_number; ++j){
				
				var selected = document.createElement("td");
				
				if (servings[day][i][j] == -1){
					selected.classList.add("null");
				}
				else if (servings[day][i][j] == 0){
					selected.classList.add("empty");
				}
				else{
					selected.classList.add("eaten");
					selected.innerHTML = calories[i];
					total_calories += calories[i];
					
				}
				
				if (servings[day][i][j] >= 0){
					selected.i = i; selected.j = j; selected.day = day;
					selected.addEventListener("click", function(){
						if (this.classList.contains("empty")){
							this.classList.remove("empty");
							this.classList.add("eaten");
							this.innerHTML = calories[this.i];
							total_calories += calories[this.i];
							servings[this.day][this.i][this.j] = 1;
						}
						else{
							this.classList.remove("eaten");
							this.classList.add("empty");
							this.innerHTML = "";
							total_calories -= calories[this.i];
							servings[this.day][this.i][this.j] = 0;
						}
						
						localStorage.setItem("servings",servings);
						
						update_calories();
					
					}, false);
			
				}
				new_row.appendChild(selected);
			}
			table.appendChild(new_row);
		}
		
	body.insertBefore(table,$("#total_calories_box"));
	
		var table_rows = $s("tr");
	for(var i = 0; i < table_rows.length; ++i){
		if(table_rows[i].id != "title_row"){
			table_rows[i].id = "std_row";
		}
	}
	localStorage.setItem("servings",servings);

	update_calories();
}

function update_calories(){

	$("#daily_calories").innerHTML = total_calories;

}

