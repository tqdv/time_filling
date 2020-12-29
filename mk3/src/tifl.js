(function() {

// See <https://tympanus.net/codrops/2015/07/16/styling-svg-use-content-css/> for SVG styling

const SVG_NS = 'http://www.w3.org/2000/svg';

/// Convert hexagon coordinates to cartesian coordinates
function hexagon2cartesian (hex_coord) {
	return [
		hex_coord[0] + 1/2 * hex_coord[1],
		Math.sqrt(3)/2 * hex_coord[1],
	]
}

const zip = (a, b) => Array.from(Array(Math.min(a.length, b.length)), (_, i) => [a[i], b[i]]);

copyAttribute = (element, attribute, other) => element.setAttribute(attribute, other.getAttribute(attribute));

class Display {
	instance = null;
	ID = 'time_filling';
	CSS_ID = 'time_filling_css';
	SVG_WIDTH = 400;

	constructor () {
		if (Display.instance instanceof Display) {
			return Display.instance;
		}

		this.initialize();
		this.draw();

		Display.instance = this;
	}

	deletePrevious() {
		document.getElementById(this.ID)?.remove();
		document.getElementById(this.CSS_ID)?.remove();
	}

	initialize() {
		let s = document.createElementNS(SVG_NS, 'svg');
		s.setAttribute('id', this.ID);
		s.setAttribute('width', this.SVG_WIDTH);
		let d = document.createElementNS(SVG_NS, 'defs');
		
		// Our reference hexagon, styled with --hexagon-color
		let p = document.createElementNS(SVG_NS, 'polygon');
		p.setAttribute('id', 'hexagon');
		p.setAttribute('points', "0 1, 0.866 0.5, 0.866 -0.5, 0 -1, -0.866 -0.5, -0.866 0.5");
		p.setAttribute('transform', "scale(0.5)");
		p.setAttribute('fill', 'rgb(235, 237, 240)')
		p.setAttribute('style', `
			shape-rendering: geometricPrecision;
			fill: var(--hexagon-color, rgb(235, 237, 240));
		`);

		d.appendChild(p)
		s.appendChild(d);
		this.defs = d;
		this.elt = s;

		let c = document.createElement('style');
		c.setAttribute('id', this.CSS_ID);
		c.textContent = `
			.hexagon-level-0 { --hexagon-color: var(--color-calendar-graph-day-bg) }
			.hexagon-level-1 { --hexagon-color: var(--color-calendar-graph-day-L1-bg) }
			.hexagon-level-2 { --hexagon-color: var(--color-calendar-graph-day-L2-bg) }
			.hexagon-level-3 { --hexagon-color: var(--color-calendar-graph-day-L3-bg) }
			.hexagon-level-4 { --hexagon-color: var(--color-calendar-graph-day-L4-bg) }

			.hexagon-red { --hexagon-color: red }
			.hexagon-green { --hexagon-color: green }

			#${this.ID} {
				display:block;
				margin: auto;
			}
		`;
		this.css = c;
	}

	draw() {
		let gh_svg = document.getElementsByClassName('js-calendar-graph-svg')[0];
		let gh_cells = gh_svg.getElementsByTagNameNS(SVG_NS, 'rect');
		let gh_tooltip = document.getElementsByClassName("svg-tip")[0];

		// Draw on a blank slate
		this.elt.replaceChildren(this.defs);

		// Calculate bounding box for svg viewBox
		let minX, minY, maxX, maxY;
		let hex_coord = hexagon2cartesian(solution[0]);
		minX = maxX = hex_coord[0];
		minY = maxY = hex_coord[1];
		for (let [hex_coord, gh_rect] of zip(solution, gh_cells)) {
			let coordinates = hexagon2cartesian(hex_coord);
			if (coordinates[0] < minX) { minX = coordinates[0] }
			if (coordinates[0] > maxX) { maxX = coordinates[0] }
			if (coordinates[1] < minY) { minY = coordinates[1] }
			if (coordinates[1] > maxY) { maxY = coordinates[1] }

			// Crete element and our position attributes
			let h = document.createElementNS(SVG_NS, 'use');
			h.setAttribute('href', '#hexagon');
			h.setAttribute('x', coordinates[0]);
			h.setAttribute('y', coordinates[1]);
			h.setAttribute('hexCoord', `${hex_coord[0]} ${hex_coord[1]}`);

			// Copy github data and styling
			copyAttribute(h, 'data-count', gh_rect);
			copyAttribute(h, 'data-date', gh_rect);
			
			let gh_fill = gh_rect.getAttribute('fill');
			let level = gh_fill.indexOf('--color-calendar-graph-day-L');
			if (level == -1) {
				h.classList.add('hexagon-level-0');
			} else {
				h.classList.add('hexagon-level-' + gh_fill[level+'--color-calendar-graph-day-L'.length]);
			}

			// if (hex_coord[1] == 0) { h.classList.add('hexagon-red') }
			// if (hex_coord[0] == 0) { h.classList.add('hexagon-green') }
			
			this.elt.appendChild(h);
		}

		this.elt.setAttribute('viewBox', `${minX-1} ${minY-1} ${maxX-minX+2} ${maxY-minY+2}`);
		let svg_local_width = maxX-minX+2;

		for (let elt of this.elt.getElementsByTagNameNS(SVG_NS, 'use')) {
			let svg = this.elt;
			// Add tooltip behaviour
			elt.addEventListener('mouseover', e => {
				// The accurate calculation is hard, so we just use heuristics and approximations
				// let svg_rect = svg.getBoundingClientRect();
				// let bbox = e.target.getBBox(); // TODO scale
				// let left = scrollX + svg_rect.left + bbox.x * this.SVG_WIDTH/svg_local_width;
				// let top = scrollY + svg_rect.top + bbox.y * this.SVG_WIDTH/svg_local_width;

				gh_tooltip.setAttribute('style', `pointer-events: none; top: ${e.pageY - 12*4 - 5}px; left: ${e.pageX - 92}px;`)
				gh_tooltip.removeAttribute('hidden');

				let contribs = e.target.getAttribute('data-count');
				let date = e.target.getAttribute('data-date');
				gh_tooltip.textContent = `${contribs} contributions on ${date}`;
			})

			elt.addEventListener('mouseleave', e => {
				gh_tooltip.setAttribute('hidden', '');
			})
		}
	}
}

let solution = [[-10,-1],[-10,0],[-9,-1],[-9,-2],[-8,-2],[-8,-1],[-9,0],[-8,0],[-7,-1],[-6,-1],[-6,0],[-7,1],[-7,0],[-8,1],[-9,2],[-9,1],[-10,1],[-11,2],[-10,2],[-11,3],[-10,3],[-9,3],[-9,4],[-8,4],[-8,3],[-8,2],[-7,2],[-7,3],[-6,2],[-5,2],[-4,1],[-4,0],[-5,1],[-6,1],[-5,0],[-5,-1],[-4,-1],[-3,-2],[-3,-3],[-4,-2],[-4,-3],[-5,-2],[-6,-2],[-7,-2],[-7,-3],[-6,-4],[-6,-3],[-5,-4],[-5,-3],[-4,-4],[-3,-4],[-3,-5],[-4,-5],[-3,-6],[-2,-6],[-2,-5],[-1,-5],[-2,-4],[-2,-3],[-1,-3],[0,-4],[-1,-4],[0,-5],[1,-6],[1,-5],[2,-5],[3,-6],[2,-6],[3,-7],[2,-7],[1,-7],[1,-8],[0,-8],[0,-7],[0,-6],[-1,-6],[-1,-7],[-1,-8],[-2,-7],[-3,-7],[-2,-8],[-3,-8],[-2,-9],[-1,-9],[0,-9],[0,-10],[1,-11],[2,-11],[1,-10],[1,-9],[2,-10],[2,-9],[2,-8],[3,-8],[3,-9],[3,-10],[4,-10],[4,-9],[5,-9],[4,-8],[4,-7],[5,-7],[5,-8],[6,-9],[6,-8],[7,-9],[8,-9],[8,-10],[7,-10],[8,-11],[9,-11],[9,-10],[9,-9],[10,-10],[11,-10],[10,-9],[11,-9],[10,-8],[9,-8],[9,-7],[10,-7],[9,-6],[10,-6],[9,-5],[8,-5],[8,-6],[8,-7],[7,-6],[7,-7],[8,-8],[7,-8],[6,-7],[6,-6],[5,-5],[4,-5],[5,-6],[4,-6],[3,-5],[3,-4],[4,-4],[5,-4],[6,-4],[6,-5],[7,-5],[7,-4],[6,-3],[5,-3],[4,-2],[3,-1],[2,-1],[2,-2],[3,-2],[4,-3],[3,-3],[2,-3],[2,-4],[1,-4],[0,-3],[1,-3],[1,-2],[0,-2],[-1,-1],[-1,-2],[-2,-1],[-2,-2],[-3,-1],[-3,0],[-2,0],[-1,0],[-1,1],[0,1],[0,0],[0,-1],[1,-1],[1,0],[2,0],[1,1],[2,1],[3,0],[3,1],[2,2],[1,2],[0,2],[0,3],[-1,3],[-1,4],[-2,4],[-2,3],[-1,2],[-2,2],[-2,1],[-3,1],[-4,2],[-3,2],[-4,3],[-3,3],[-3,4],[-3,5],[-4,6],[-4,5],[-5,6],[-5,5],[-4,4],[-5,4],[-5,3],[-6,3],[-6,4],[-6,5],[-7,5],[-7,4],[-8,5],[-8,6],[-9,7],[-9,6],[-9,5],[-10,6],[-10,7],[-10,8],[-11,9],[-11,10],[-10,9],[-10,10],[-9,9],[-9,8],[-8,8],[-7,7],[-8,7],[-7,6],[-6,6],[-6,7],[-7,8],[-7,9],[-8,9],[-9,10],[-9,11],[-8,11],[-8,10],[-7,10],[-6,9],[-6,8],[-5,7],[-4,7],[-5,8],[-5,9],[-4,8],[-4,9],[-3,8],[-2,8],[-2,9],[-3,9],[-4,10],[-3,10],[-2,10],[-1,9],[-1,10],[-2,11],[-1,11],[0,10],[0,9],[1,9],[2,8],[2,9],[3,8],[3,7],[2,7],[1,8],[1,7],[0,8],[-1,8],[0,7],[1,6],[0,6],[-1,7],[-2,7],[-3,7],[-3,6],[-2,5],[-2,6],[-1,6],[-1,5],[0,5],[0,4],[1,3],[2,3],[2,4],[1,4],[1,5],[2,5],[2,6],[3,6],[4,5],[3,5],[4,4],[3,4],[3,3],[4,3],[4,2],[3,2],[4,1],[5,1],[5,2],[5,3],[5,4],[6,3],[6,4],[7,3],[7,2],[6,2],[7,1],[8,0],[8,-1],[7,0],[6,1],[6,0],[7,-1],[6,-1],[5,0],[5,-1],[4,0],[4,-1],[5,-2],[6,-2],[7,-2],[7,-3],[8,-4],[9,-4],[8,-3],[8,-2],[9,-3],[9,-2],[10,-3],[10,-2],[11,-3],[11,-2],[10,-1],[9,-1],[9,0],[8,1],[8,2],[9,2],[10,1],[9,1],[10,0],[11,0],[12,-1],[11,-1],[12,-2],[13,-2],[13,-1],[12,0],[13,0],[13,1],[14,1],[14,0],[15,0],[15,-1],[14,-1],[14,-2],[14,-3],[15,-4],[16,-4],[15,-3],[15,-2],[16,-3],[17,-3],[18,-3],[17,-2],[16,-2],[16,-1],[17,-1],[18,-2]];

let container = document.getElementsByClassName("js-yearly-contributions")[0]

let disp = new Display();
disp.deletePrevious();
container.insertAdjacentElement('beforebegin', disp.elt);
document.head.appendChild(disp.css);

const contribution_ctn = document.getElementById('year-list-container')
	.parentElement
	.getElementsByTagName('div')[0];
const observer = new MutationObserver((mutationsList, observer) => {
	for (let mutation of mutationsList) {
		let has_changed = false;
		mutation.addedNodes.forEach(e => has_changed ||= e.classList?.contains('js-yearly-contributions'));
		if (has_changed) {
			// Redraw hexagons
			disp.draw();
		}
	}
});

// Start observing the target node for configured mutations
observer.observe(contribution_ctn, { attributes: false, childList: true, subtree: false });

}());