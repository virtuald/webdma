/*
    WebDMA
    Copyright (C) 2009 Dustin Spicuzza <dustin@virtualroadside.com>
	
	$Id$

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License v3 as published by
    the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
	TODO: This file has quickly turned into a mess. Need to reorganize it
	into some objects or something... 
*/


$(document).ready(function() 
{
	// show/hide the variable groups to make the layout less cluttered
	$(".grouphdr").each(function(idx, thing){
		$(thing).mousedown(function(){
		
			$(this).next().toggle("slow");
				
			return false;
		});
	});
	
	// setup static vars
	$(".readonlyvar").each(function(idx, thing)
	{
		$(this).data('ajax_outstanding', false);
	});
	
	// checkboxes
	$(".booleans").each(function(idx, thing){
	
		var params = this.id.split("_");
		$(this).data('bar', params);
		$(this).data('ajax_outstanding', false);
		
		this.id = params[0] + "_" + params[1];
		
		// various browsers keep the checkbox values over refreshes
		if (params[2] == 'checked')
			this.checked = true;
		else
			this.checked = false;
		
		$(this).click(function(e)
		{
			var params = $(this).data('bar');
			
			if (this.checked)
				params[2] = 1;
			else
				params[2] = 0;
			
			submit_variables(this, params);
		});
		
	});
	
	$(".selectbar").hover(
		function(){
			$(this).addClass("selectbar_hovered");
		},
		function(){
			$(this).removeClass("selectbar_hovered");
		}
	);

	
	// make the bars come to life (integers)
	$(".selectbar").each(function(idx, thing){
		
		/* 
			bar parameters are done using the id tag:
				0 - group
				1 - variable name
				2 - current value
				3 - min
				4 - max
				5 - step
				
				6 is set by the code, and is the floating point
				precision (which is inferred from the step size)
				
				If the numeric items have a p in them, that is
				actually a decimal point.
		*/
		
		// get the id from the element, split to params
		var params = this.id.split("_");
		
		params[6] = 0;
		for (i = 2; i < 6; i++)
			if (params[i].indexOf('p') != -1)
			{
				if (i == 5) params[6] = params[i].length - params[i].indexOf('p') - 1;
				params[i] = parseFloat(params[i].replace(/p/,'.'));
			}
			else
				params[i] = parseInt(params[i]);
						
		// add the inner divs, transform it into a nice bar
		var barhtml = "";
		
		barhtml += "<div class=\"lt\">-</div>";
		barhtml += "<div class=\"bar\" id=\"" + params[0] + "_" + params[1] + "\"><div>&nbsp;</div><span>" + params[2] + "</span></div>";
		barhtml += "<div class=\"gt\">+</div>";
		
		$(thing).html(barhtml);
		
		// select the child, and attach the parameters to it
		var bar = $(thing).children(".bar");
		bar.data('bar', params);
		
		// set the id so we can find it later
		
		// setup the parameters
		update_parameters(bar, false);

		bar.children("div:first-child").width(((params[2] - params[3])/(params[4] - params[3]))*100 + "%");
		
		bar.data('down', false);
		bar.data('ajax_outstanding', false);
		
		bar.hover(
			function() {},
			function() {
				$(this).data('down', false);
			}
		)
		.mousedown(function(e){
			$(this).data('down', true);
			dragFn(this, e);
			return false;
		})
		.mouseup(function(){
			$(this).data('down', false);
			return false;
		})
		.mousemove(function(e){
			dragFn(this, e);
			return false;
		});
		
		// setup the adjustment tabs on each end
		$(thing).children(".lt,.gt")
		.hover(
			function() {
				$(this).addClass("ltgt_hovered");
			},
			function() {
				// cancels the step timer, just in case
				$(this).data('mv-enabled', false);
				$(this).removeClass("ltgt_hovered");
			}
		)
		.mousedown(function(e){
			
			// pin these variables down so the timeout function can use them
			var data = this;
			var that = $(this).siblings('.bar');
			var stepsz = $(this).hasClass('gt') ? 1 : -1;
			$(this).data('mv-enabled', true);
			
			step_bar(that, stepsz);
				
			// setup a timer that allows us to repeat the step until the 
			// mouse is released
			var fn = function(){ 
				if ($(data).data('mv-enabled'))
				{
					step_bar(that, stepsz);
					setTimeout(fn, 100);
				}
			}
			
			setTimeout(fn, 600);
			return false;
		})
		.mouseup(function(e){
			// cancel the timer
			$(this).data('mv-enabled', false);
			return false;
		});
	});
	
	// finally, set a timer to update stuff every 100 ms or so
	start_ajax_loop();
});

function dragFn(that, e)
{
	if ($(that).data('down') == true)
	{
		var params = $(that).data('bar');
		var diff = params[4] - params[3];
		
		var x = e.clientX 
				- parseInt($(that).offset().left) 
				- parseInt('0' + $(that).css('borderLeftWidth'));
		var w = $(that).innerWidth();
		
	
		
		// determine the value by converting the mouse position into a ratio
		params[2] = (x / w) * diff;
		
		// adjust it to be on a step size boundary
		params[2] = Math.round(params[2] / params[5]) * params[5] + params[3];
					
		update_parameters(that);
	}
}

function set_bar(that, val)
{
	var params = $(that).data('bar');
	
	if (params[2] == val)
		return;
	params[2] = val;
	update_parameters(that, false);
}

function step_bar(that, val)
{
	var params = $(that).data('bar');
	params[2] += params[5] * val;
			
	update_parameters(that);
}

function update_parameters(that, dosubmit)
{
	var params = $(that).data('bar');
	var diff = params[4] - params[3];
	
	// ensure its not too big
	if (params[2] > params[4])
		params[2] = params[4];
	else if (params[2] < params[3])
		params[2] = params[3];
	
	// then convert it back and display it
	$(that).children("div:first-child").width(((params[2] - params[3]) / diff)*100 + "%");
	if (params[6] == 0)
		$(that).children("span").html(params[2]);
	else
		$(that).children("span").html(params[2].toFixed(params[6]));
		
	if (dosubmit !== false)
		submit_variables(that, params);
}

var ajax_errors = 0;

function ajaxError(x, status, e) {

	ajax_errors += 1;
	var current_error = ajax_errors;

	current_error += 1;
	// display something somewhere to indicate an error
	$('body').append(
		"<div id=\"err" + current_error + "\" style=\"display: none\">" +
			"<strong>ERROR</strong>: an error occurred while communicating with the server! (" + status + ")" +
		"</div>"
	);
		
	$('#err' + current_error).show(1000, function() {
		setTimeout(function()
		{
			$('#err' + current_error).hide("slow", function() { 
				$(this).remove(); 
			});
		}, 5000);
	});
}


// submits a variable change to the server
function submit_variables(that, params)
{
	if ($(that).data('ajax_outstanding') != true)
	{
		// only do the submission every 50 ms or so
		$(that).data('ajax_outstanding', true);
		
		setTimeout(
			function(){
				$.ajax({
					type: "POST",
					url: "/varcontrol",
					data: 
						"group=" + params[0].substr(1) + 
						"&var=" + params[1].substr(1) + 
						"&value=" + params[2] +
						"&instance=" + current_instance,
					dataType: "json",
					
					error: ajaxError,
					
					success: function(data, status) {
					
						// display something somewhere to indicate success?
						switch (data.status)
						{
							case "FAIL":
							case "INVALID":
								$(that).addClass("error");
								break;
							case "OK":
								$(that).removeClass("error");
								break;
							case "RELOAD":
								window.location.reload();
								return;
						}
						
						$(that).data('ajax_outstanding', false);
					}
				});
			},
			50
		);
	}
}

function start_ajax_loop()
{
	var fn = function(){
		$.ajax({
			type: "POST",
			url: "/varcontrol",
			data: "getupdate=true",
			dataType: "json",
			error: function(x, status, e) {
				setTimeout(fn, 2500);
				ajaxError(x, status, e);
			},
			success: function(data, status) {
			
				if (data.instance != current_instance)
				{
					window.location.reload();
					return;
				}
			
				// update all of the data items returned
				$.each( data , function( key, val )
				{
					var obj = $('#' + key);
					if (obj.length && obj.data('ajax_outstanding') == false)
					{					
						switch (obj.attr('tagName').toLowerCase())
						{
							case 'div':
								set_bar( obj, val );
								break;
							case 'span':
								obj.html(val);
								break;
							case 'input':
								if (val)
									obj.attr('checked', 'checked');
								else
									obj.removeAttr('checked');
								
								break;
						}
					}
				});
				
				setTimeout(fn, 150);
			}
		});
	};
	
	setTimeout(fn, 150);
}


