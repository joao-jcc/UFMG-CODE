import logo from '../img/health-logo.png';
import user from '../img/user1.png';
import searchIcon from '../img/search-icon.png';
import '../style/App.css';
import '../style/calendar.css'
import Calendar from './Calendar';

function App() {
  return <Page />;
}


function Page() {
  const page = (
    <div className='wrapper'>
      <Header />
      <MainContent />
    </div>
  )

  return page;
}

function Header() {
  const header_ = (
    <header>

      <div id='header-left'>

        <div class='circular-image'>
          <img id='logo' src={logo} alt='' ></img>
        </div>

        <h1 id='logo-title'>Health Diary</h1>

      </div>

    
      <div id='header-right'>
        <div className="search-container">
          <input type='text' placeholder='Search'></input>
          <img src={searchIcon} alt='search icon' className="search-icon" />
        </div>
        <div class='circular-image'>
          <img id='user-img' src={user} alt='' ></img>
        </div>
      </div>

    </header>
  )
  
  return header_;
}


function MainContent() {
  const mainContent = (
    <div id="main-content">
      <div id="side-bar">
        {/* Sidebar content */}
      </div>

      <div id="content">
        <Calendar />
      </div>
    </div>
  );

  return mainContent;
}
export default App;
