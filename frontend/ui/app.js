// UI Navigation
function showDashboard() {
    document.getElementById('main-dashboard').style.display = 'grid';
    document.getElementById('universe-detail').style.display = 'none';
    document.querySelector('.tab:nth-child(1)').classList.add('active');
    document.querySelector('.tab:nth-child(2)').classList.remove('active');
}

function showUniverseDetail() {
    document.getElementById('main-dashboard').style.display = 'none';
    document.getElementById('universe-detail').style.display = 'block';
    document.querySelector('.tab:nth-child(1)').classList.remove('active');
    document.querySelector('.tab:nth-child(2)').classList.add('active');
}

function viewUniverse(id) {
    showUniverseDetail();
    // TODO: Load universe details from backend
    console.log('Loading universe:', id);
}

// Form handling
document.getElementById('universe-form').onsubmit = function(e) {
    e.preventDefault();
    const formData = new FormData(e.target);
    const universeData = {
        matterDensity: parseFloat(formData.get('matterDensity')),
        darkEnergyDensity: parseFloat(formData.get('darkEnergyDensity')),
        hubbleConstant: parseFloat(formData.get('hubbleConstant')),
        matterAntimatterRatio: parseFloat(formData.get('matterAntimatterRatio')),
        darkEnergyW: parseFloat(formData.get('darkEnergyW'))
    };
    
    // TODO: Send data to backend
    console.log('Creating universe with parameters:', universeData);
}; 