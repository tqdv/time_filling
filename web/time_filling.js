'use strict';

let log = console.log;

/** @namespace */
const TimeFilling = {

/** The JSON for the last year hex positions
 * @type {Array.<{x: Number, y: Number}>}
 */
last_year_hex_pos: [{"x": -10.5, "y": 0.866025},{"x": -10, "y": 0},{"x": -9, "y": 0},{"x": -8.5, "y": 0.866025},{"x": -9.5, "y": 0.866025},{"x": -10, "y": 1.73205},{"x": -9, "y": 1.73205},{"x": -8, "y": 1.73205},{"x": -8.5, "y": 2.59808},{"x": -8, "y": 3.4641},{"x": -7, "y": 3.4641},{"x": -7.5, "y": 2.59808},{"x": -7, "y": 1.73205},{"x": -6.5, "y": 2.59808},{"x": -5.5, "y": 2.59808},{"x": -4.5, "y": 2.59808},{"x": -4, "y": 1.73205},{"x": -5, "y": 1.73205},{"x": -6, "y": 1.73205},{"x": -5.5, "y": 0.866025},{"x": -4.5, "y": 0.866025},{"x": -4, "y": 0},{"x": -5, "y": 0},{"x": -4.5, "y": -0.866025},{"x": -3.5, "y": -0.866025},{"x": -4, "y": -1.73205},{"x": -5, "y": -1.73205},{"x": -5.5, "y": -0.866025},{"x": -6.5, "y": -0.866025},{"x": -6, "y": 0},{"x": -6.5, "y": 0.866025},{"x": -7, "y": 0},{"x": -7.5, "y": 0.866025},{"x": -8, "y": 0},{"x": -7.5, "y": -0.866025},{"x": -8.5, "y": -0.866025},{"x": -9.5, "y": -0.866025},{"x": -10, "y": -1.73205},{"x": -9.5, "y": -2.59808},{"x": -9, "y": -1.73205},{"x": -8, "y": -1.73205},{"x": -8.5, "y": -2.59808},{"x": -7.5, "y": -2.59808},{"x": -7, "y": -1.73205},{"x": -6, "y": -1.73205},{"x": -6.5, "y": -2.59808},{"x": -5.5, "y": -2.59808},{"x": -6, "y": -3.4641},{"x": -7, "y": -3.4641},{"x": -6.5, "y": -4.33013},{"x": -5.5, "y": -4.33013},{"x": -5, "y": -5.19615},{"x": -6, "y": -5.19615},{"x": -7, "y": -5.19615},{"x": -6.5, "y": -6.06218},{"x": -5.5, "y": -6.06218},{"x": -5, "y": -6.9282},{"x": -6, "y": -6.9282},{"x": -6.5, "y": -7.79423},{"x": -5.5, "y": -7.79423},{"x": -6, "y": -8.66025},{"x": -5, "y": -8.66025},{"x": -4.5, "y": -7.79423},{"x": -4, "y": -8.66025},{"x": -3.5, "y": -9.52628},{"x": -2.5, "y": -9.52628},{"x": -3, "y": -8.66025},{"x": -2, "y": -8.66025},{"x": -2.5, "y": -7.79423},{"x": -3.5, "y": -7.79423},{"x": -4, "y": -6.9282},{"x": -3, "y": -6.9282},{"x": -2.5, "y": -6.06218},{"x": -3.5, "y": -6.06218},{"x": -4.5, "y": -6.06218},{"x": -4, "y": -5.19615},{"x": -3, "y": -5.19615},{"x": -3.5, "y": -4.33013},{"x": -4.5, "y": -4.33013},{"x": -5, "y": -3.4641},{"x": -4, "y": -3.4641},{"x": -4.5, "y": -2.59808},{"x": -3.5, "y": -2.59808},{"x": -3, "y": -3.4641},{"x": -2.5, "y": -4.33013},{"x": -2, "y": -5.19615},{"x": -1.5, "y": -4.33013},{"x": -2, "y": -3.4641},{"x": -1, "y": -3.4641},{"x": -0.5, "y": -4.33013},{"x": -1, "y": -5.19615},{"x": -1.5, "y": -6.06218},{"x": -2, "y": -6.9282},{"x": -1.5, "y": -7.79423},{"x": -1, "y": -6.9282},{"x": -0.5, "y": -7.79423},{"x": 0, "y": -6.9282},{"x": -0.5, "y": -6.06218},{"x": 0.5, "y": -6.06218},{"x": 0, "y": -5.19615},{"x": 0.5, "y": -4.33013},{"x": 1, "y": -5.19615},{"x": 1.5, "y": -4.33013},{"x": 2, "y": -5.19615},{"x": 1.5, "y": -6.06218},{"x": 1, "y": -6.9282},{"x": 0.5, "y": -7.79423},{"x": 1, "y": -8.66025},{"x": 2, "y": -8.66025},{"x": 1.5, "y": -7.79423},{"x": 2, "y": -6.9282},{"x": 2.5, "y": -7.79423},{"x": 3, "y": -8.66025},{"x": 3.5, "y": -9.52628},{"x": 4.5, "y": -9.52628},{"x": 4, "y": -8.66025},{"x": 5, "y": -8.66025},{"x": 4.5, "y": -7.79423},{"x": 3.5, "y": -7.79423},{"x": 3, "y": -6.9282},{"x": 4, "y": -6.9282},{"x": 3.5, "y": -6.06218},{"x": 2.5, "y": -6.06218},{"x": 3, "y": -5.19615},{"x": 4, "y": -5.19615},{"x": 4.5, "y": -6.06218},{"x": 5, "y": -6.9282},{"x": 5.5, "y": -7.79423},{"x": 6.5, "y": -7.79423},{"x": 7, "y": -6.9282},{"x": 6, "y": -6.9282},{"x": 5.5, "y": -6.06218},{"x": 6.5, "y": -6.06218},{"x": 6, "y": -5.19615},{"x": 6.5, "y": -4.33013},{"x": 6, "y": -3.4641},{"x": 5, "y": -3.4641},{"x": 5.5, "y": -4.33013},{"x": 5, "y": -5.19615},{"x": 4.5, "y": -4.33013},{"x": 3.5, "y": -4.33013},{"x": 4, "y": -3.4641},{"x": 3, "y": -3.4641},{"x": 2.5, "y": -4.33013},{"x": 2, "y": -3.4641},{"x": 2.5, "y": -2.59808},{"x": 3.5, "y": -2.59808},{"x": 3, "y": -1.73205},{"x": 2, "y": -1.73205},{"x": 1.5, "y": -0.866025},{"x": 2.5, "y": -0.866025},{"x": 3.5, "y": -0.866025},{"x": 3, "y": 0},{"x": 2, "y": 0},{"x": 2.5, "y": 0.866025},{"x": 1.5, "y": 0.866025},{"x": 2, "y": 1.73205},{"x": 3, "y": 1.73205},{"x": 2.5, "y": 2.59808},{"x": 1.5, "y": 2.59808},{"x": 1, "y": 1.73205},{"x": 0.5, "y": 0.866025},{"x": -0.5, "y": 0.866025},{"x": -1, "y": 0},{"x": 0, "y": 0},{"x": 1, "y": 0},{"x": 0.5, "y": -0.866025},{"x": -0.5, "y": -0.866025},{"x": 0, "y": -1.73205},{"x": 1, "y": -1.73205},{"x": 1.5, "y": -2.59808},{"x": 0.5, "y": -2.59808},{"x": 1, "y": -3.4641},{"x": 0, "y": -3.4641},{"x": -0.5, "y": -2.59808},{"x": -1.5, "y": -2.59808},{"x": -1, "y": -1.73205},{"x": -1.5, "y": -0.866025},{"x": -2, "y": -1.73205},{"x": -2.5, "y": -2.59808},{"x": -3, "y": -1.73205},{"x": -2.5, "y": -0.866025},{"x": -2, "y": 0},{"x": -3, "y": 0},{"x": -3.5, "y": 0.866025},{"x": -2.5, "y": 0.866025},{"x": -3, "y": 1.73205},{"x": -2, "y": 1.73205},{"x": -1.5, "y": 0.866025},{"x": -1, "y": 1.73205},{"x": 0, "y": 1.73205},{"x": 0.5, "y": 2.59808},{"x": -0.5, "y": 2.59808},{"x": 0, "y": 3.4641},{"x": -1, "y": 3.4641},{"x": -1.5, "y": 2.59808},{"x": -2.5, "y": 2.59808},{"x": -3.5, "y": 2.59808},{"x": -3, "y": 3.4641},{"x": -2, "y": 3.4641},{"x": -2.5, "y": 4.33013},{"x": -3.5, "y": 4.33013},{"x": -4, "y": 3.4641},{"x": -4.5, "y": 4.33013},{"x": -5, "y": 3.4641},{"x": -6, "y": 3.4641},{"x": -5.5, "y": 4.33013},{"x": -6.5, "y": 4.33013},{"x": -6, "y": 5.19615},{"x": -5, "y": 5.19615},{"x": -5.5, "y": 6.06218},{"x": -6.5, "y": 6.06218},{"x": -7, "y": 6.9282},{"x": -6, "y": 6.9282},{"x": -6.5, "y": 7.79423},{"x": -5.5, "y": 7.79423},{"x": -5, "y": 6.9282},{"x": -4, "y": 6.9282},{"x": -4.5, "y": 6.06218},{"x": -4, "y": 5.19615},{"x": -3.5, "y": 6.06218},{"x": -3, "y": 5.19615},{"x": -2.5, "y": 6.06218},{"x": -3, "y": 6.9282},{"x": -3.5, "y": 7.79423},{"x": -4.5, "y": 7.79423},{"x": -5, "y": 8.66025},{"x": -4, "y": 8.66025},{"x": -4.5, "y": 9.52628},{"x": -3.5, "y": 9.52628},{"x": -3, "y": 8.66025},{"x": -2.5, "y": 7.79423},{"x": -2, "y": 8.66025},{"x": -1, "y": 8.66025},{"x": -1.5, "y": 7.79423},{"x": -0.5, "y": 7.79423},{"x": -1, "y": 6.9282},{"x": -2, "y": 6.9282},{"x": -1.5, "y": 6.06218},{"x": -0.5, "y": 6.06218},{"x": 0, "y": 5.19615},{"x": -1, "y": 5.19615},{"x": -2, "y": 5.19615},{"x": -1.5, "y": 4.33013},{"x": -0.5, "y": 4.33013},{"x": 0.5, "y": 4.33013},{"x": 1, "y": 3.4641},{"x": 2, "y": 3.4641},{"x": 1.5, "y": 4.33013},{"x": 2.5, "y": 4.33013},{"x": 2, "y": 5.19615},{"x": 1, "y": 5.19615},{"x": 0.5, "y": 6.06218},{"x": 1.5, "y": 6.06218},{"x": 2, "y": 6.9282},{"x": 1, "y": 6.9282},{"x": 0, "y": 6.9282},{"x": 0.5, "y": 7.79423},{"x": 1.5, "y": 7.79423},{"x": 2.5, "y": 7.79423},{"x": 2, "y": 8.66025},{"x": 2.5, "y": 9.52628},{"x": 3, "y": 8.66025},{"x": 3.5, "y": 9.52628},{"x": 4, "y": 8.66025},{"x": 3.5, "y": 7.79423},{"x": 3, "y": 6.9282},{"x": 2.5, "y": 6.06218},{"x": 3, "y": 5.19615},{"x": 3.5, "y": 6.06218},{"x": 4, "y": 5.19615},{"x": 4.5, "y": 6.06218},{"x": 4, "y": 6.9282},{"x": 4.5, "y": 7.79423},{"x": 5, "y": 8.66025},{"x": 6, "y": 8.66025},{"x": 6.5, "y": 7.79423},{"x": 5.5, "y": 7.79423},{"x": 5, "y": 6.9282},{"x": 6, "y": 6.9282},{"x": 5.5, "y": 6.06218},{"x": 6.5, "y": 6.06218},{"x": 7, "y": 5.19615},{"x": 6.5, "y": 4.33013},{"x": 6, "y": 5.19615},{"x": 5, "y": 5.19615},{"x": 5.5, "y": 4.33013},{"x": 4.5, "y": 4.33013},{"x": 3.5, "y": 4.33013},{"x": 3, "y": 3.4641},{"x": 3.5, "y": 2.59808},{"x": 4, "y": 3.4641},{"x": 5, "y": 3.4641},{"x": 4.5, "y": 2.59808},{"x": 4, "y": 1.73205},{"x": 3.5, "y": 0.866025},{"x": 4, "y": 0},{"x": 4.5, "y": 0.866025},{"x": 5, "y": 1.73205},{"x": 5.5, "y": 0.866025},{"x": 5, "y": 0},{"x": 5.5, "y": -0.866025},{"x": 4.5, "y": -0.866025},{"x": 4, "y": -1.73205},{"x": 5, "y": -1.73205},{"x": 4.5, "y": -2.59808},{"x": 5.5, "y": -2.59808},{"x": 6, "y": -1.73205},{"x": 7, "y": -1.73205},{"x": 6.5, "y": -2.59808},{"x": 7, "y": -3.4641},{"x": 7.5, "y": -2.59808},{"x": 8, "y": -3.4641},{"x": 8.5, "y": -2.59808},{"x": 8, "y": -1.73205},{"x": 9, "y": -1.73205},{"x": 10, "y": -1.73205},{"x": 10.5, "y": -0.866025},{"x": 9.5, "y": -0.866025},{"x": 10, "y": 0},{"x": 9, "y": 0},{"x": 8.5, "y": -0.866025},{"x": 7.5, "y": -0.866025},{"x": 8, "y": 0},{"x": 7.5, "y": 0.866025},{"x": 7, "y": 0},{"x": 6.5, "y": -0.866025},{"x": 6, "y": 0},{"x": 6.5, "y": 0.866025},{"x": 6, "y": 1.73205},{"x": 5.5, "y": 2.59808},{"x": 6, "y": 3.4641},{"x": 7, "y": 3.4641},{"x": 6.5, "y": 2.59808},{"x": 7, "y": 1.73205},{"x": 7.5, "y": 2.59808},{"x": 8.5, "y": 2.59808},{"x": 9.5, "y": 2.59808},{"x": 9, "y": 1.73205},{"x": 8, "y": 1.73205},{"x": 8.5, "y": 0.866025},{"x": 9.5, "y": 0.866025},{"x": 10, "y": 1.73205},{"x": 10.5, "y": 0.866025},{"x": 11, "y": 0},{"x": 11.5, "y": 0.866025},{"x": 11, "y": 1.73205},{"x": 12, "y": 1.73205},{"x": 12.5, "y": 0.866025},{"x": 12, "y": 0},{"x": 13, "y": 0},{"x": 13.5, "y": -0.866025},{"x": 14.5, "y": -0.866025},{"x": 15, "y": 0},{"x": 14, "y": 0},{"x": 13.5, "y": 0.866025},{"x": 14.5, "y": 0.866025},{"x": 15, "y": 1.73205},{"x": 15.5, "y": 0.866025},{"x": 16.5, "y": 0.866025},{"x": 16, "y": 1.73205},{"x": 17, "y": 1.73205},{"x": 16.5, "y": 2.59808},{"x": 15.5, "y": 2.59808},{"x": 14.5, "y": 2.59808},{"x": 14, "y": 1.73205},{"x": 13, "y": 1.73205},{"x": 13.5, "y": 2.59808},{"x": 12.5, "y": 2.59808},{"x": 13, "y": 3.4641},{"x": 14, "y": 3.4641}],

/**
 * The calContainer is the div that contains the overview tab, which is
 * the calendar and the list of commits
 *
 * The calElement is the said calendar of the calContainer. It contains
 * the SVG calendar as well as the surrounding text
 */

/**
 * Retrieves the calElement
 * @returns {?Element} null on error
 */
getCalElement: function () {
	let e;
	e = document.getElementsByClassName('js-yearly-contributions');
	if (e.length == 0) return null;
	e = e[0];
	return e;
},

/**
 * Retrieves the calContainer
 * @returns {?Element} null on error
 */
getCalContainer: function () {
	let cal = TimeFilling.getCalElement();
	if (cal === null) return null;
	if (cal.parentNode === undefined) return null;
	return cal.parentNode;
},

/**
 * Checks if an Element is the calElement
 * @param {Element}
 * @returns {Bool}
 */
isCalElement: function (elt) {
	let e;
	e = elt;
	if (e.classList === undefined) return false;
	e = e.classList.contains('js-yearly-contributions');
	return e;
},

/**
 * Extracts the calElement from a NodeList
 * @param {NodeList}
 * @returns {?Element} null on error
 */
extractCalElement: function (newNodes) {
	let calElement = Array.from(newNodes).find(isCalElement);
	if (calElement === undefined) return null;
	return calElement;
},

/**
 * Returns the year selected in the contribution activity pane as a Number
 * @returns {?Number} null on error
 */
getContributionYear: function () {
	let yearContainer = document.querySelector('.js-year-link.selected');
	if (yearContainer === null) return null;
	return Number(yearContainer.textContent);
},

/** @namespace */
Graph: {
	/** The svg node that contains the graph
	 * @type {?SVGElement}
	 */
	 graph: null,
	 /** The currently selected year. it is null if none is selected
	  * @type {?Number}
	  */
	 year: null,


	 /** The class for the svg element that contains the templates
	  * @type {String}
	  */
	 svg_template_class: 'svg-template',

	/** Create a new $graph */
	create: function () {
		this.graph = document.createElementNS('http://www.w3.org/2000/svg', 'svg');
		this.graph.setAttribute('width', 600);
		this.graph.setAttribute ('height', 400);
	},

	/** Insert $graph in the document
	 * It doesn't check for duplicates
	 * @returns {null} null on error
	 */
	insert: function () {
		// ghGraph is the box containing the calendar and some legend
		let ghGraph = (function () {
			let e;
			e = document.getElementsByClassName('graph-before-activity-overview');
			if (e.length == 0) return null;
			e = e[0];
			return e;
		}());
		if (ghGraph === null) return null;

		ghGraph.insertAdjacentElement('afterend', this.graph);
	},


	/** Insert into $graph all the day hexagons */
	populate: function () {

		let days = document.getElementsByClassName('day');

		// this.graph.appendChild(days[0]);

		let i = 0
		for (let d of TimeFilling.last_year_hex_pos) {
			let e = document.createElementNS('http://www.w3.org/2000/svg', 'use');
			e.setAttribute('href', '#' + this.hex_id);
			e.setAttribute('x', d.x);
			e.setAttribute('y', d.y);
			e.setAttribute('id', 'hexagon' + i);
			this.graph.appendChild(e);
			i++;
		}

		// for (let day of Array.from(days)) { // Have a non-live collection
		// 	this.graph.appendChild(day);
		// }

		// let hexs = [];
		// let i = 0;
		// for (let day of days) {
		// 	let hex = document.createElement('use');
		//
		// 	// Copy all attributes
		// 	for (let attr of day.attributes) {
		// 		hex.setAttribute(attr.name, attr.value);
		// 	}
		//
		// 	hex.setAttribute('href', "#hexagon");
		// 	hex.setAttribute('id', "hex-day" + i);
		// 	hex.setAttribute('x', /* */);
		// 	hex.setAttribute('y', /* */);
		// 	// Make sure not to add it to the document yet,
		// 	// otherwise infinite loop
		// 	hex.classList.add('day', 'hex');
		//
		// 	hexs.push(hex);
		//
		// 	i++;
		// }
		//
		// for (let hex of hexs) {
		// 	graph.insertAdjacentElement('beforeend', hex);
		// }
	},


	/** Create a new $graph and replace it because it gets deleted */
	update: function () {
		let n_year = TimeFilling.getContributionYear ();
		if (n_year == this.year) {
			// Deal with the active cell potentially changing
			//WIP
		} else {
			this.year = n_year;
			log (`New year: ${this.year}`);

			this.createGraph();
			this.populateGraph();
		}

		this.insertGraph();
		log(this.graph);
	},
}, // Graph

/** @namespace */
Hexagon: {
	/** The id of the hexagon svg
	 * @type {String}
	 */
	id: 'hexagon',

	/** Create the $hex element
	 * @returns {SVGElement} the svg element containing the hexagon template
	 */
	create: function () {
		let s = document.createElementNS('http://www.w3.org/2000/svg', 'svg');
		s.classList.add(TimeFilling.svg_template_class);
		s.setAttribute('display', 'none');

		let p = document.createElementNS('http://www.w3.org/2000/svg', 'polygon');
		p.setAttribute('id', this.id);
		p.setAttribute('points', "0 1, 0.866 0.5, 0.866 -0.5, 0 -1, -0.866 -0.5, -0.866 0.5");
		p.setAttribute('transform', "scale(0.5)");

		s.appendChild(p);
		return s;
	},

	/** Does the Hexagon element exist ?
	 * @returns {Bool}
	 */
	 exists: function () {
		 return document.getElementById(this.id) !== null;
	 },

	/** Inserts the hexagon $h into the document without duplication
	 * @returns {?Bool} whether we inserted a new element or not, null on error
	 */
	insert: function () {
		if (this.exists()) return false;

		let elt = this.create();
		document.body.appendChild(elt);
		return true;
	}
}, // Hexagon

/** @namespace */
css: {
	/** The id for the style element
	 * @type {String}
	 */
	id: 'time_filling-css',

	/** Creates the CSS code
	 * @returns {String} the CSS text
	 */
	createText: function () {
		let e =
``
		;
		return e;
	},

	/** Does the stylesheet exist in the document ?
	 * @returns {Bool}
	 */
	exists: function () {
		return document.getElementById(this.css_id) !== null;
	},

	/** Creates a style element
	 * @returns {HTMLElement}
	 */
	create: function () {
		let text = this.createText();
		let elt = document.createElement('style');
		elt.textContent = text;
		elt.setAttribute('id', this.id);
		return elt;
	},

	/** Adds CSS styling to the document without duplicating
	 * @returns {Bool} whether a new element was created or not
	 */
	insert: function () {
		if (this.exists()) return false;

		let elt = this.create();
		document.head.appendChild(elt);

		return true;
	},
}, // css

/** Initialize TimeFilling */
init: function () {
	this.css.insert();
	this.Hexagon.insert();
}

}; // TimeFilling
TimeFilling.init();



(function(){

	const calContainer = TimeFilling.getCalContainer ();
	if (calContainer === null) return;

	let observer = new MutationObserver((mutationList, observer) => {
		for (let mutationRecord of mutationList) {
			(function () {
				let calElement = TimeFilling.extractCalElement (mutationRecord.addedNodes);
				if (calElement === null) return;

				TimeFilling.Graph.update()
			}());
		}
	});

	let options = { childList: true, };
	observer.observe(calContainer, options);

	TimeFilling.Graph.update();

}());
