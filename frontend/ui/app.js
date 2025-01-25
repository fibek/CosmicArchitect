// UI Navigation
function showDashboard() {
    document.getElementById('main-dashboard').style.display = 'block';
    document.getElementById('universe-detail').style.display = 'none';
    document.querySelector('.tab:nth-child(1)').classList.add('active');
    document.querySelector('.tab:nth-child(2)').classList.remove('active');
    loadUniverseList();
}

function showUniverseDetail() {
    document.getElementById('main-dashboard').style.display = 'none';
    document.getElementById('universe-detail').style.display = 'block';
    document.querySelector('.tab:nth-child(1)').classList.remove('active');
    document.querySelector('.tab:nth-child(2)').classList.add('active');
}

async function loadUniverseList() {
    try {
        const response = await webui.call('getUniverses');
        const data = JSON.parse(response);
        
        if (data.status === 'success') {
            const universeList = document.getElementById('universe-list');
            universeList.innerHTML = '';
            
            if (data.universes.length === 0) {
                universeList.innerHTML = '<p>No universes created yet. Create your first universe!</p>';
                return;
            }
            
            data.universes.forEach(universe => {
                const item = document.createElement('div');
                item.className = 'universe-item';
                item.innerHTML = `
                    <h3>${universe.name}</h3>
                    <p>Matter Density: ${universe.matterDensity}</p>
                    <p>Dark Energy Density: ${universe.darkEnergyDensity}</p>
                    <div class="universe-actions">
                        <button onclick="viewUniverse(${universe.id})">View Details</button>
                        <button class="delete-btn" onclick="deleteUniverse(${universe.id}, '${universe.name}')">Delete</button>
                    </div>
                `;
                universeList.appendChild(item);
            });
        } else {
            console.error('Failed to load universes:', data.message);
        }
    } catch (error) {
        console.error('Error loading universes:', error);
    }
}

function formatTimestamp(timestamp) {
    if (timestamp === null || timestamp === undefined || isNaN(timestamp)) {
        return "Does not occur";
    }
    
    // Convert to number and handle special cases
    timestamp = Number(timestamp);
    if (timestamp === 0) return "t = 0";
    if (timestamp === Infinity || timestamp > 1e100) return "t → ∞";
    if (timestamp < 0) return "Does not occur";
    
    // Convert to years (timestamp is in billions of years)
    const years = timestamp * 1e9;
    
    if (years < 1) {
        // For times less than a year, convert to seconds
        const seconds = years * 365.25 * 24 * 60 * 60;
        if (seconds < 1e-6) return `t = ${(seconds * 1e9).toFixed(2)} nanoseconds`;
        if (seconds < 1e-3) return `t = ${(seconds * 1e6).toFixed(2)} microseconds`;
        if (seconds < 1) return `t = ${(seconds * 1e3).toFixed(2)} milliseconds`;
        if (seconds < 60) return `t = ${seconds.toFixed(2)} seconds`;
        if (seconds < 3600) return `t = ${(seconds / 60).toFixed(2)} minutes`;
        if (seconds < 86400) return `t = ${(seconds / 3600).toFixed(2)} hours`;
        return `t = ${(seconds / 86400).toFixed(2)} days`;
    }
    
    if (years < 1e3) return `t = ${years.toFixed(2)} years`;
    if (years < 1e6) return `t = ${(years / 1e3).toFixed(2)} thousand years`;
    if (years < 1e9) return `t = ${(years / 1e6).toFixed(2)} million years`;
    return `t = ${(years / 1e9).toFixed(2)} billion years`;
}

function getMilestoneTitle(type) {
    const titles = {
        'BIG_BANG': "Big Bang",
        'INFLATION': "Inflation",
        'PARTICLE_ERA': "Particle Era",
        'NUCLEOSYNTHESIS': "Nucleosynthesis",
        'RECOMBINATION': "Recombination",
        'DARK_AGES': "Dark Ages",
        'FIRST_STARS': "First Stars",
        'GALAXY_FORMATION': "Galaxy Formation",
        'ACCELERATED_EXPANSION': "Accelerated Expansion",
        'BIG_RIP': "Big Rip",
        'HEAT_DEATH': "Heat Death",
        'BIG_CRUNCH': "Big Crunch"
    };
    return titles[type] || "Unknown Milestone";
}

async function viewUniverse(id) {
    try {
        console.log('Fetching universe data for ID:', id);
        const response = await webui.call('getUniverses');
        console.log('Raw response from backend:', response);
        
        const data = JSON.parse(response);
        console.log('Parsed universe data:', data);
        
        if (data.status === 'success') {
            const universe = data.universes.find(u => u.id === id);
            console.log('Selected universe:', universe);
            
            if (!universe) {
                throw new Error('Universe not found');
            }
            
            // Display universe parameters
            const paramsDiv = document.getElementById('universe-params');
            paramsDiv.innerHTML = `
                <div class="param-group">
                    <div class="param-item">
                        <div class="param-label">Matter Density (Ω_m)</div>
                        <div class="param-value">${universe.matterDensity}</div>
                    </div>
                    <div class="param-item">
                        <div class="param-label">Dark Energy Density (Ω_Λ)</div>
                        <div class="param-value">${universe.darkEnergyDensity}</div>
                    </div>
                    <div class="param-item">
                        <div class="param-label">Hubble Constant (H₀)</div>
                        <div class="param-value">${universe.hubbleConstant}</div>
                    </div>
                    <div class="param-item">
                        <div class="param-label">Matter/Antimatter Ratio</div>
                        <div class="param-value">${universe.matterAntimatterRatio}</div>
                    </div>
                    <div class="param-item">
                        <div class="param-label">Dark Energy w</div>
                        <div class="param-value">${universe.darkEnergyW}</div>
                    </div>
                </div>
            `;
            
            // Display timeline
            console.log('Displaying timeline with milestones:', universe.milestones);
            const timelineDiv = document.getElementById('milestone-timeline');
            timelineDiv.innerHTML = '';
            
            universe.milestones.forEach((milestone, index) => {
                console.log(`Processing milestone ${index}:`, milestone);
                const milestoneElement = document.createElement('div');
                milestoneElement.className = 'milestone';
                milestoneElement.innerHTML = `
                    <div class="milestone-content">
                        <div class="milestone-title">${getMilestoneTitle(milestone.type)}</div>
                        <div class="milestone-time">t = ${formatTimestamp(milestone.timestamp)}</div>
                        <div class="milestone-description">${milestone.description || ''}</div>
                    </div>
                `;
                timelineDiv.appendChild(milestoneElement);
            });
            
            // Switch to universe detail view
            document.getElementById('main-dashboard').style.display = 'none';
            document.getElementById('universe-detail').style.display = 'block';
            
        } else {
            throw new Error(data.message || 'Failed to load universe data');
        }
    } catch (error) {
        console.error('Error viewing universe:', error);
        alert('Error viewing universe: ' + error.message);
    }
}

// Delete universe function
async function deleteUniverse(id, name) {
    if (confirm(`Are you sure you want to delete universe "${name}"?`)) {
        try {
            const response = await webui.call('deleteUniverse', JSON.stringify({ id }));
            const data = JSON.parse(response);
            
            if (data.status === 'success') {
                alert('Universe deleted successfully');
                loadUniverseList(); // Refresh the list
            } else {
                throw new Error(data.message);
            }
        } catch (error) {
            console.error('Error deleting universe:', error);
            alert('Error deleting universe: ' + error.message);
        }
    }
}

// Update form submission
document.getElementById('universe-form').addEventListener('submit', async function(e) {
    e.preventDefault();
    
    const formData = new FormData(e.target);
    const universeData = {
        name: formData.get('name'),
        matterDensity: parseFloat(formData.get('matterDensity')),
        darkEnergyDensity: parseFloat(formData.get('darkEnergyDensity')),
        hubbleConstant: parseFloat(formData.get('hubbleConstant')),
        matterAntimatterRatio: parseFloat(formData.get('matterAntimatterRatio')),
        darkEnergyW: parseFloat(formData.get('darkEnergyW'))
    };
    
    try {
        const response = await webui.call('createUniverse', JSON.stringify(universeData));
        const data = JSON.parse(response);
        
        if (data.status === 'success') {
            showDashboard();
            loadUniverseList();
            e.target.reset();
        } else {
            alert('Error creating universe: ' + data.message);
        }
    } catch (error) {
        alert('Error creating universe: ' + error.message);
    }
});

// Initial load
document.addEventListener('DOMContentLoaded', () => {
    showDashboard();
}); 