// UI Navigation
function showDashboard() {
    const detailView = document.getElementById('universe-detail');
    const timelineView = document.getElementById('timeline-view');
    const universeList = document.getElementById('universe-list');
    
    // Hide other views with animation
    detailView.classList.add('view-transition', 'fade-out');
    timelineView.classList.add('view-transition', 'fade-out');
    
    setTimeout(() => {
        detailView.style.display = 'none';
        timelineView.style.display = 'none';
        universeList.classList.add('view-transition', 'fade-in');
        universeList.style.display = 'grid';
    }, 300);
}

function showTimeline() {
    const detailView = document.getElementById('universe-detail');
    const timelineView = document.getElementById('timeline-view');
    
    // Hide detail view with animation
    detailView.classList.add('view-transition', 'fade-out');
    
    setTimeout(() => {
        detailView.style.display = 'none';
        timelineView.style.display = 'block';
        timelineView.classList.add('view-transition', 'fade-in');
        
        // Trigger milestone animations
        const milestones = timelineView.querySelectorAll('.milestone');
        milestones.forEach(milestone => {
            milestone.classList.add('visible');
        });
    }, 300);
}

function hideTimeline() {
    const detailView = document.getElementById('universe-detail');
    const timelineView = document.getElementById('timeline-view');
    
    // Hide timeline view with animation
    timelineView.classList.add('view-transition', 'fade-out');
    
    setTimeout(() => {
        timelineView.style.display = 'none';
        detailView.style.display = 'block';
        detailView.classList.add('view-transition', 'fade-in');
    }, 300);
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

let currentUniverseId = null;  // Add this at the top of the file

// Wait for WebSocket connection
function waitForWebSocket() {
    return new Promise((resolve, reject) => {
        if (webui.isConnected()) {
            resolve();
            return;
        }

        const maxAttempts = 10;
        let attempts = 0;
        
        const checkConnection = () => {
            attempts++;
            if (webui.isConnected()) {
                resolve();
            } else if (attempts >= maxAttempts) {
                reject(new Error('Failed to connect to backend server'));
            } else {
                setTimeout(checkConnection, 500);
            }
        };
        
        checkConnection();
    });
}

// Update the viewUniverse function to use webui
async function viewUniverse(id) {
    currentUniverseId = id;
    try {
        await waitForWebSocket();
        const response = await webui.call('getUniverses');
        const data = JSON.parse(response);
        
        if (data.status !== 'success') {
            throw new Error(data.message || 'Failed to load universes');
        }
        
        const universe = data.universes.find(u => u.id === id);
        if (!universe) {
            throw new Error('Universe not found');
        }
        
        showUniverseDetail(universe);
    } catch (error) {
        showNotification('Failed to load universe: ' + error.message, 'is-danger');
    }
}

// Update the deleteUniverse function to use webui
async function deleteUniverse(id, name) {
    if (confirm(`Are you sure you want to delete universe "${name}"?`)) {
        try {
            await waitForWebSocket();
            const response = await webui.call('deleteUniverse', JSON.stringify({ id }));
            const data = JSON.parse(response);
            
            if (data.status !== 'success') {
                throw new Error(data.message);
            }
            
            showNotification('Universe deleted successfully', 'is-success');
            updateUniverseList();
        } catch (error) {
            showNotification('Failed to delete universe: ' + error.message, 'is-danger');
        }
    }
}

// Add delete functionality to universe items
function addDeleteButton(universeElement, universe) {
    const deleteButton = document.createElement('button');
    deleteButton.className = 'button is-danger is-small ml-2';
    deleteButton.innerHTML = '<span class="icon"><i class="fas fa-trash"></i></span>';
    deleteButton.onclick = (e) => {
        e.stopPropagation(); // Prevent triggering the universe item click
        deleteUniverse(universe.id, universe.name);
    };
    
    const actionsDiv = document.createElement('div');
    actionsDiv.className = 'media-right';
    actionsDiv.appendChild(deleteButton);
    
    universeElement.querySelector('.media').appendChild(actionsDiv);
}

// Update the universe list rendering to include delete buttons
async function updateUniverseList() {
    try {
        await waitForWebSocket();
        const response = await webui.call('getUniverses');
        const data = JSON.parse(response);
        
        if (data.status !== 'success') {
            throw new Error(data.message || 'Failed to load universes');
        }
        
        const universes = data.universes;
        const universeList = document.getElementById('universe-list');
        universeList.innerHTML = '';
        
        if (universes.length === 0) {
            universeList.innerHTML = `
                <div class="empty-state">
                    <p class="title is-4 has-text-light">No Universes Yet</p>
                    <p class="subtitle is-6 has-text-light">Create your first universe using the form on the left</p>
                </div>
            `;
            return;
        }
        
        universes.forEach(universe => {
            const universeElement = document.createElement('div');
            universeElement.className = 'box has-background-grey-darker universe-item';
            universeElement.innerHTML = `
                <article class="media">
                    <div class="media-content">
                        <div class="content has-text-light">
                            <p>
                                <strong class="has-text-light">${universe.name}</strong>
                                <br>
                                <small class="has-text-grey-lighter">Created: ${new Date(universe.createdAt).toLocaleString()}</small>
                            </p>
                            <div class="tags">
                                <span class="tag is-primary">Ω_m: ${universe.matterDensity}</span>
                                <span class="tag is-primary">Ω_Λ: ${universe.darkEnergyDensity}</span>
                                <span class="tag is-primary">H₀: ${universe.hubbleConstant}</span>
                            </div>
                        </div>
                    </div>
                </article>
            `;
            universeElement.addEventListener('click', () => viewUniverse(universe.id));
            addDeleteButton(universeElement, universe);
            universeList.appendChild(universeElement);
        });
        
        document.getElementById('universe-count').textContent = universes.length;
    } catch (error) {
        console.error('Full error:', error);
        showNotification('Failed to load universes: ' + error.message, 'is-danger');
    }
}

// Universe detail view
function showUniverseDetail(universe) {
    const detailView = document.getElementById('universe-detail');
    const universeList = document.getElementById('universe-list');
    const timelineView = document.getElementById('timeline-view');
    
    // Hide list view with animation
    universeList.classList.add('view-transition', 'fade-out');
    
    setTimeout(() => {
        universeList.style.display = 'none';
        detailView.style.display = 'block';
        detailView.classList.add('view-transition', 'fade-in');
        
        // Update universe parameters
        const paramsSection = document.getElementById('universe-params');
        paramsSection.innerHTML = `
            <div class="content has-text-light">
                <h3 class="title is-4 has-text-light">${universe.name}</h3>
                <div class="columns is-multiline">
                    <div class="column is-half">
                        <p><strong>Matter Density (Ω_m):</strong> <span class="has-text-weight-bold">${universe.matterDensity}</span></p>
                        <p><strong>Dark Energy Density (Ω_Λ):</strong> <span class="has-text-weight-bold">${universe.darkEnergyDensity}</span></p>
                        <p><strong>Hubble Constant (H₀):</strong> <span class="has-text-weight-bold">${universe.hubbleConstant}</span></p>
                    </div>
                    <div class="column is-half">
                        <p><strong>Matter/Antimatter Ratio:</strong> <span class="has-text-weight-bold">${universe.matterAntimatterRatio}</span></p>
                        <p><strong>Dark Energy W:</strong> <span class="has-text-weight-bold">${universe.darkEnergyW}</span></p>
                    </div>
                </div>
            </div>
        `;
        
        // Update timeline
        if (universe.milestones) {
            const timeline = document.getElementById('milestone-timeline');
            timeline.innerHTML = '';
            
            const validMilestones = universe.milestones.filter(milestone => 
                milestone.timestamp !== null && 
                milestone.timestamp !== undefined && 
                !isNaN(milestone.timestamp) && 
                milestone.timestamp >= 0
            );
            
            if (validMilestones.length === 0) {
                timeline.innerHTML = `
                    <div class="timeline-empty">
                        <i class="fas fa-info-circle fa-2x mb-3"></i>
                        <p>No timeline events occur in this universe configuration.</p>
                    </div>
                `;
                return;
            }
            
            validMilestones.forEach((milestone) => {
                const milestoneElement = document.createElement('div');
                milestoneElement.className = 'milestone';
                milestoneElement.innerHTML = `
                    <div class="content has-text-light">
                        <p class="heading has-text-light">
                            <i class="fas fa-clock"></i>
                            ${formatTimestamp(milestone.timestamp)}
                        </p>
                        <p class="title is-6 has-text-light">${getMilestoneTitle(milestone.type)}</p>
                        <p class="subtitle is-7 has-text-grey-lighter">${milestone.description || ''}</p>
                    </div>
                `;
                timeline.appendChild(milestoneElement);
            });
        }
    }, 300);
}

// Search functionality
const searchUniverses = debounce(async (query) => {
    const universeItems = document.querySelectorAll('.universe-item');
    universeItems.forEach(item => {
        const name = item.querySelector('strong').textContent.toLowerCase();
        if (name.includes(query.toLowerCase())) {
            item.style.display = '';
        } else {
            item.style.display = 'none';
        }
    });
}, 300);

// Notification system
function showNotification(message, type) {
    const notification = document.createElement('div');
    notification.className = `notification ${type} is-light`;
    notification.innerHTML = `
        <button class="delete"></button>
        ${message}
    `;
    
    notification.querySelector('.delete').addEventListener('click', () => {
        notification.remove();
    });
    
    document.body.appendChild(notification);
    setTimeout(() => notification.remove(), 5000);
}

// Update export functions to use webui
async function exportUniverse(format) {
    if (currentUniverseId === null) {
        alert('No universe selected');
        return;
    }

    try {
        await waitForWebSocket();
        const response = await webui.call('exportUniverse', JSON.stringify({
            id: currentUniverseId,
            format: format
        }));
        const data = JSON.parse(response);
        
        if (data.status !== 'success') {
            throw new Error(data.message);
        }
        
        // Create a download link
        const blob = new Blob([data.data], { 
            type: format === 'json' ? 'application/json' : 'text/csv',
            endings: 'native'
        });
        const url = window.URL.createObjectURL(blob);
        const a = document.createElement('a');
        a.style.display = 'none';
        a.href = url;
        const timestamp = new Date().toISOString().replace(/[:.]/g, '-');
        a.download = `universe_${currentUniverseId}_${timestamp}.${format}`;
        
        document.body.appendChild(a);
        a.click();
        
        window.URL.revokeObjectURL(url);
        document.body.removeChild(a);
    } catch (error) {
        showNotification('Failed to export universe: ' + error.message, 'is-danger');
    }
}

async function exportAllUniverses(format) {
    try {
        await waitForWebSocket();
        const response = await webui.call('exportAllUniverses', JSON.stringify({ format }));
        const data = JSON.parse(response);
        
        if (data.status !== 'success') {
            throw new Error(data.message);
        }
        
        // Create a download link
        const blob = new Blob([data.data], { 
            type: format === 'json' ? 'application/json' : 'text/csv',
            endings: 'native'
        });
        const url = window.URL.createObjectURL(blob);
        const a = document.createElement('a');
        a.style.display = 'none';
        a.href = url;
        const timestamp = new Date().toISOString().replace(/[:.]/g, '-');
        a.download = `all_universes_${timestamp}.${format}`;
        
        document.body.appendChild(a);
        a.click();
        
        window.URL.revokeObjectURL(url);
        document.body.removeChild(a);
    } catch (error) {
        showNotification('Failed to export universes: ' + error.message, 'is-danger');
    }
}

// Debounce function to limit API calls
function debounce(func, wait) {
    let timeout;
    return function executedFunction(...args) {
        const later = () => {
            clearTimeout(timeout);
            func(...args);
        };
        clearTimeout(timeout);
        timeout = setTimeout(later, wait);
    };
}

// Initial load
document.addEventListener('DOMContentLoaded', () => {
    updateUniverseList();
});

// Universe creation form handling
document.getElementById('universe-form').addEventListener('submit', async (e) => {
    e.preventDefault();
    const formData = new FormData(e.target);
    const rawData = Object.fromEntries(formData.entries());
    
    // Convert numerical fields to numbers
    const universeData = {
        name: rawData.name,
        matterDensity: parseFloat(rawData.matterDensity),
        darkEnergyDensity: parseFloat(rawData.darkEnergyDensity),
        hubbleConstant: parseFloat(rawData.hubbleConstant),
        matterAntimatterRatio: parseFloat(rawData.matterAntimatterRatio),
        darkEnergyW: parseFloat(rawData.darkEnergyW)
    };
    
    try {
        await waitForWebSocket();
        const response = await webui.call('createUniverse', JSON.stringify(universeData));
        const data = JSON.parse(response);
        
        if (data.status === 'success') {
            updateUniverseList();
            showNotification('Universe created successfully!', 'is-success');
            e.target.reset();
        } else {
            throw new Error(data.message);
        }
    } catch (error) {
        showNotification('Failed to create universe: ' + error.message, 'is-danger');
    }
}); 