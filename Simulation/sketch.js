let sun, earth, moon;
let G = 0.2;
let orbitPath = [];
let moonOrbitPath = [];
let grid = [];
let gridSpacing = 30;
let curvatureIntensity = 0.8;
let deltaTime = 0.8;

function setup() {
  createCanvas(1200, 800, WEBGL);
  angleMode(DEGREES);

  // Initialize celestial bodies with realistic parameters
  sun = {
    position: createVector(0, 0),
    mass: 100500,
    radius: 50,
    velocity: createVector(0, 0),
    color: [255, 225, 50]
  };

  earth = {
    position: createVector(300, 0),
    mass: 3600,
    radius: 10,
    velocity: createVector(0, 8.5),
    color: [70, 130, 200]
  };

  moon = {
    position: createVector(earth.position.x + 35, earth.position.y),
    mass: 100,
    radius: 3,
    velocity: createVector(0, 4.2).add(earth.velocity),
    color: [200, 200, 200]
  };

  createGrid();
  noStroke();
}

function createGrid() {
  grid = [];
  const range = 400;
  for (let x = -range; x <= range; x += gridSpacing) {
    let col = [];
    for (let y = -range; y <= range; y += gridSpacing) {
      col.push(createVector(x, y, 0));
    }
    grid.push(col);
  }
}

function draw() {
  background(0);
  lights();
  orbitControl(1, 1, 0.1);
  
  // Camera adjustment for better view
  translate(-width/4.5, -height/4.5);
  scale(0.75);

  updatePhysics();
  drawSpacetimeFabric();
  drawCelestialBodies();
  drawOrbitPaths();
}

function updatePhysics() {
  // Calculate gravitational interactions
  const earthSunForce = calculateGravity(earth, sun);
  const moonSunForce = calculateGravity(moon, sun);
  const moonEarthForce = calculateGravity(moon, earth);

  // Update velocities (Earth primarily affected by Sun, Moon by both Earth and Sun)
  earth.velocity.add(p5.Vector.div(earthSunForce, earth.mass).mult(deltaTime));
  moon.velocity.add(p5.Vector.div(moonSunForce.add(moonEarthForce), moon.mass).mult(deltaTime));

  // Update positions
  earth.position.add(p5.Vector.mult(earth.velocity, deltaTime));
  moon.position.add(p5.Vector.mult(moon.velocity, deltaTime));

  // Update spacetime curvature
  updateSpacetimeCurvature();
  
  // Store orbital paths
  orbitPath.push(earth.position.copy());
  moonOrbitPath.push(moon.position.copy());
  if (orbitPath.length > 400) orbitPath.shift();
  if (moonOrbitPath.length > 100) moonOrbitPath.shift();
}

function calculateGravity(body1, body2) {
  const direction = p5.Vector.sub(body2.position, body1.position);
  const distance = direction.mag();
  direction.normalize();
  const strength = (G * body1.mass * body2.mass) / (distance * distance);
  return direction.mult(strength);
}

function updateSpacetimeCurvature() {
  for (let x = 0; x < grid.length; x++) {
    for (let y = 0; y < grid[x].length; y++) {
      const point = grid[x][y];
      const dSun = dist(point.x, point.y, sun.position.x, sun.position.y);
      const dEarth = dist(point.x, point.y, earth.position.x, earth.position.y);
      const dMoon = dist(point.x, point.y, moon.position.x, moon.position.y);
      
      // Realistic curvature proportions
      point.z = (-sun.mass * 0.8)/(dSun + 10) - 
                (earth.mass * 0.15)/(dEarth + 20) -
                (moon.mass * 0.05)/(dMoon + 30);
    }
  }
}

function drawSpacetimeFabric() {
  stroke(120, 180, 255, 120);
  strokeWeight(1.2);
  noFill();
  
  for (let x = 0; x < grid.length - 1; x++) {
    for (let y = 0; y < grid[x].length - 1; y++) {
      beginShape();
      vertex(grid[x][y].x, grid[x][y].y, grid[x][y].z * 1000);
      vertex(grid[x+1][y].x, grid[x+1][y].y, grid[x+1][y].z * 1000);
      vertex(grid[x+1][y+1].x, grid[x+1][y+1].y, grid[x+1][y+1].z * 1000);
      vertex(grid[x][y+1].x, grid[x][y+1].y, grid[x][y+1].z * 1000);
      endShape(CLOSE);
    }
  }
}

function drawCelestialBodies() {
  // Draw Sun
  push();
  translate(sun.position.x, sun.position.y);
  emissiveMaterial(...sun.color);
  pointLight(255, 255, 220, 0, 0, 0);
  sphere(sun.radius);
  pop();

  // Draw Earth
  push();
  translate(earth.position.x, earth.position.y);
  emissiveMaterial(...earth.color);
  sphere(earth.radius);
  pop();

  // Draw Moon
  push();
  translate(moon.position.x, moon.position.y);
  emissiveMaterial(...moon.color);
  sphere(moon.radius);
  pop();
}

function drawOrbitPaths() {
  // Earth's orbit path
  noFill();
  stroke(50, 200, 100, 150);
  beginShape();
  orbitPath.forEach(pos => vertex(pos.x, pos.y));
  endShape();

  // Moon's orbit path
  stroke(180, 180, 180, 120);
  beginShape();
  moonOrbitPath.forEach(pos => vertex(pos.x, pos.y));
  endShape();
}

function keyPressed() {
  if (key === 'p' || key === 'P') {
    togglePause();
  }
}

function togglePause() {
  if (isLooping()) {
    noLoop();
  } else {
    loop();
  }
}