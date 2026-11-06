with open('frontend/templates/dashboard.html', 'r', encoding='utf-8') as f:
    html = f.read()

# 1. Refactor Hero Section: Remove canvas, emojis layer, useless drop-badge, sparkle-pill, and un-tilt the 3 showcase cards
old_hero = '''<!-- ==========================================================================
     FRONT HERO COVER SCREEN (FERNWOOD-STYLE AESTHETIC + 3D SHOWCASE CARDS)
     ========================================================================== -->
<section id="heroScreen" class="fernwood-hero-section">
  <!-- Live Ambient Lightning & Nebula Canvas -->
  <canvas id="thunderCanvas"></canvas>

  <!-- Cartoon Animated Layer (Stickman Scholars, Bouncing Books, Graduation Caps) -->
  <div class="cartoon-floating-layer">
    <!-- Stickman Scholars -->
    <div class="cartoon-item cartoon-stickman" style="top: 14%; left: 6%;">🧑‍🎓</div>
    <div class="cartoon-item cartoon-stickman" style="top: 24%; right: 7%; animation-delay: -3s;">🧑‍🎓</div>
    <div class="cartoon-item cartoon-stickman" style="bottom: 24%; left: 8%; animation-delay: -1.5s;">🧑‍🎓</div>

    <!-- Bouncing Books -->
    <div class="cartoon-item cartoon-book" style="top: 18%; left: 22%; animation-delay: -0.6s;">📚</div>
    <div class="cartoon-item cartoon-book" style="bottom: 28%; right: 10%; animation-delay: -1.8s;">📖</div>
    <div class="cartoon-item cartoon-book" style="top: 48%; right: 4%; animation-delay: -2.4s;">📚</div>

    <!-- Floating Graduation Caps & Scrolls -->
    <div class="cartoon-item cartoon-mortarboard" style="top: 10%; right: 24%; animation-delay: -1s;">🎓</div>
    <div class="cartoon-item cartoon-mortarboard" style="bottom: 18%; right: 26%; animation-delay: -2.8s;">🎓</div>
    <div class="cartoon-item cartoon-scroll" style="bottom: 20%; left: 24%; animation-delay: -3.2s;">📜</div>
  </div>

  <!-- Dot Matrix Vignette Pattern Elements -->
  <div class="hero-dot-matrix-left"></div>
  <div class="hero-dot-matrix-right"></div>

  <!-- Floating Tilted Badge (NEW DROP style) -->
  <div class="floating-drop-badge">
    <span>TOP</span>
    <span>MERIT</span>
  </div>

  <!-- Hero Main Stage Content -->
  <div class="hero-stage-container">
    <!-- Top Sub-Nav Breadcrumb Indicators -->
    <div class="hero-subnav-links">
      <a href="#students-section" class="hero-sublink">→ Live Rankings</a>
      <a href="#dsa-section" class="hero-sublink">→ DSA Benchmarks</a>
      <a href="#syllabus-section" class="hero-sublink">→ 100% Syllabus</a>
    </div>

    <!-- Giant Headline with Floating Sparkle Icon -->
    <div class="hero-headline-wrap">
      <div class="floating-sparkle-pill">
        <span>✦</span>
      </div>
      <h1 class="hero-headline-fernwood">
        Rank every student,<br>
        one assessment at a time.
      </h1>
    </div>

    <!-- Subtitle Text -->
    <p class="hero-subtitle-fernwood">
      Continuous marks tracking, dynamic merit rankings, and zero-compromise algorithmic precision.<br class="d-none d-md-inline">
      On your dashboard every continuous assessment.
    </p>

    <!-- Call to Action Buttons -->
    <div class="hero-cta-group">
      <a href="#cockpitStart" class="btn-fernwood-primary text-decoration-none">
        Start Ranking
      </a>
      <a href="/curriculum-graph" class="btn-fernwood-secondary text-decoration-none">
        How it works
      </a>
    </div>

    <!-- THE THREE 3D FLOATING SHOWCASE CARDS (Exact match to reference image!) -->
    <div class="hero-tilted-showcase-cards">
      
      <!-- Card 1 (Left, tilted -3.5deg): Subject Health / Progress Bars -->
      <div class="fernwood-card card-left-tilt">
        <div class="card-top-header d-flex align-items-center">
          <span class="icon-badge-violet me-2"><i class="bi bi-bar-chart-fill"></i></span>
          <span class="card-title-text">Subject Health</span>
        </div>
        <div class="card-bars-list mt-3">
          <div class="bar-row">
            <span class="bar-label">Data Structures</span>
            <div class="bar-track"><div class="bar-fill" style="width: 92%;"></div></div>
            <span class="bar-score">92</span>
          </div>
          <div class="bar-row">
            <span class="bar-label">Discrete Math</span>
            <div class="bar-track"><div class="bar-fill" style="width: 88%;"></div></div>
            <span class="bar-score">88</span>
          </div>
          <div class="bar-row">
            <span class="bar-label">Computer Arch</span>
            <div class="bar-track"><div class="bar-fill" style="width: 97%;"></div></div>
            <span class="bar-score">97</span>
          </div>
          <div class="bar-row">
            <span class="bar-label">Algorithms</span>
            <div class="bar-track"><div class="bar-fill" style="width: 74%;"></div></div>
            <span class="bar-score">74</span>
          </div>
          <div class="bar-row">
            <span class="bar-label">Lab Practical</span>
            <div class="bar-track"><div class="bar-fill" style="width: 61%;"></div></div>
            <span class="bar-score">61</span>
          </div>
        </div>
      </div>

      <!-- Card 2 (Center, featured elevated glowing purple card): Top Performer / Semi-circular Gauge -->
      <div class="fernwood-card card-center-feature">
        <div class="center-card-header text-center">
          <span class="center-subtitle">Top Performer of the Semester</span>
        </div>
        <div class="gauge-center-wrap">
          <!-- Semi-circular Speedometer SVG Gauge -->
          <svg class="gauge-svg" viewBox="0 0 200 120">
            <!-- Background Arc Track -->
            <path d="M 25 105 A 75 75 0 0 1 175 105" fill="none" stroke="rgba(255, 255, 255, 0.22)" stroke-width="14" stroke-linecap="round"/>
            <!-- Animated Progress Arc -->
            <path class="gauge-meter-path" d="M 25 105 A 75 75 0 0 1 175 105" fill="none" stroke="#ffffff" stroke-width="14" stroke-linecap="round" stroke-dasharray="235.6" stroke-dashoffset="23.5"/>
          </svg>
          <div class="gauge-score-value">92</div>
        </div>
        <div class="center-card-caption text-center">
          Hemanya Gillurkar, Thriving
        </div>
      </div>

      <!-- Card 3 (Right, tilted +3.5deg): Merit Velocity / Sparkline -->
      <div class="fernwood-card card-right-tilt">
        <div class="card-top-header d-flex align-items-center justify-content-between">
          <div class="d-flex align-items-center">
            <span class="icon-badge-violet me-2"><i class="bi bi-droplet-fill"></i></span>
            <span class="card-title-text">Merit Velocity</span>
          </div>
          <span class="pill-streak-badge">12 weeks</span>
        </div>
        <div class="sparkline-wrap mt-3">
          <!-- Smooth SVG Line Chart -->
          <svg class="sparkline-svg" viewBox="0 0 260 110">
            <!-- Subtle Gridlines -->
            <line x1="0" y1="25" x2="260" y2="25" stroke="#f1f5f9" stroke-width="1" />
            <line x1="0" y1="55" x2="260" y2="55" stroke="#f1f5f9" stroke-width="1" />
            <line x1="0" y1="85" x2="260" y2="85" stroke="#f1f5f9" stroke-width="1" />
            
            <!-- Sparkline Path Area Fill -->
            <path d="M 10 90 Q 40 85, 60 70 T 110 75 T 150 50 T 190 40 T 230 35 T 250 25 L 250 105 L 10 105 Z" fill="rgba(124, 58, 237, 0.08)" />
            <!-- Sparkline Line -->
            <path d="M 10 90 Q 40 85, 60 70 T 110 75 T 150 50 T 190 40 T 230 35 T 250 25" fill="none" stroke="#7c3aed" stroke-width="3.5" stroke-linecap="round" stroke-linejoin="round" />
            <!-- Endpoint Pulse Dot -->
            <circle cx="250" cy="25" r="4.5" fill="#7c3aed" />
          </svg>
        </div>
      </div>

    </div>
  </div>

  <!-- Scroll Down Cue -->
  <a href="#cockpitStart" class="hero-scroll-cue">
    <span>Scroll to Explore</span>
    <i class="bi bi-chevron-down fs-5"></i>
  </a>
</section>'''

new_hero = '''<!-- ==========================================================================
     FRONT HERO STAGE (CLEAN, RESTRAINED, MATCHING CORNER RADII & NO JUNK BADGES)
     ========================================================================== -->
<section id="heroScreen" class="clean-hero-section">
  <!-- Subtle Vignette Grid Background -->
  <div class="hero-dot-matrix-left"></div>
  <div class="hero-dot-matrix-right"></div>

  <!-- Hero Main Stage Content -->
  <div class="hero-stage-container">
    <!-- Functional Navigation Links -->
    <div class="hero-subnav-links">
      <a href="#mod-leaderboard" class="hero-sublink"><i class="bi bi-trophy me-1 text-warning"></i> Live Rankings</a>
      <a href="#mod-workbench" class="hero-sublink"><i class="bi bi-cpu me-1 text-info"></i> DSA Benchmarks</a>
      <a href="#mod-syllabus" class="hero-sublink"><i class="bi bi-check2-circle me-1 text-success"></i> 100% Syllabus</a>
    </div>

    <!-- Focused Headline (Clean typography, no arbitrary floating emoji/sparkle) -->
    <div class="hero-headline-wrap">
      <h1 class="hero-headline-fernwood">
        Rank every student,<br>
        one assessment at a time.
      </h1>
    </div>

    <!-- Subtitle Text -->
    <p class="hero-subtitle-fernwood">
      Continuous marks tracking, dynamic merit rankings, and zero-compromise algorithmic precision.<br class="d-none d-md-inline">
      On your dashboard every continuous assessment.
    </p>

    <!-- Call to Action Buttons -->
    <div class="hero-cta-group">
      <a href="#cockpitStart" class="btn-fernwood-primary text-decoration-none">
        Start Ranking <i class="bi bi-arrow-down-short ms-1"></i>
      </a>
      <a href="/curriculum-graph" class="btn-fernwood-secondary text-decoration-none">
        How it works <i class="bi bi-arrow-right-short ms-1"></i>
      </a>
    </div>

    <!-- FLATTENED, NON-TILTED 3-COLUMN METRICS SHOWCASE (Matching Corner Radii) -->
    <div class="hero-metric-deck">
      
      <!-- Card 1: Subject Health -->
      <div class="metric-deck-card">
        <div class="card-top-header d-flex align-items-center mb-3">
          <i class="bi bi-bar-chart-fill text-primary me-2"></i>
          <span class="card-title-text">Subject Health</span>
        </div>
        <div class="card-bars-list">
          <div class="bar-row">
            <span class="bar-label">Data Structures</span>
            <div class="bar-track"><div class="bar-fill" style="width: 92%;"></div></div>
            <span class="bar-score">92</span>
          </div>
          <div class="bar-row">
            <span class="bar-label">Discrete Math</span>
            <div class="bar-track"><div class="bar-fill" style="width: 88%;"></div></div>
            <span class="bar-score">88</span>
          </div>
          <div class="bar-row">
            <span class="bar-label">Computer Arch</span>
            <div class="bar-track"><div class="bar-fill" style="width: 97%;"></div></div>
            <span class="bar-score">97</span>
          </div>
          <div class="bar-row">
            <span class="bar-label">Algorithms</span>
            <div class="bar-track"><div class="bar-fill" style="width: 74%;"></div></div>
            <span class="bar-score">74</span>
          </div>
          <div class="bar-row">
            <span class="bar-label">Lab Practical</span>
            <div class="bar-track"><div class="bar-fill" style="width: 61%;"></div></div>
            <span class="bar-score">61</span>
          </div>
        </div>
      </div>

      <!-- Card 2: Top Performer Gauge (Grounded, non-neon elevation) -->
      <div class="metric-deck-card metric-deck-card-featured">
        <div class="center-card-header text-center mb-2">
          <span class="center-subtitle">Top Performer of the Semester</span>
        </div>
        <div class="gauge-center-wrap">
          <svg class="gauge-svg" viewBox="0 0 200 120">
            <path d="M 25 105 A 75 75 0 0 1 175 105" fill="none" stroke="rgba(255, 255, 255, 0.12)" stroke-width="12" stroke-linecap="round"/>
            <path class="gauge-meter-path" d="M 25 105 A 75 75 0 0 1 175 105" fill="none" stroke="#8b5cf6" stroke-width="12" stroke-linecap="round" stroke-dasharray="235.6" stroke-dashoffset="23.5"/>
          </svg>
          <div class="gauge-score-value">92</div>
        </div>
        <div class="center-card-caption text-center mt-2">
          Hemanya Gillurkar <span class="badge bg-success bg-opacity-20 text-success border border-success border-opacity-30 ms-1 font-monospace">Rank #1</span>
        </div>
      </div>

      <!-- Card 3: Merit Velocity Sparkline -->
      <div class="metric-deck-card">
        <div class="card-top-header d-flex align-items-center justify-content-between mb-3">
          <div class="d-flex align-items-center">
            <i class="bi bi-activity text-info me-2"></i>
            <span class="card-title-text">Merit Velocity</span>
          </div>
          <span class="badge bg-secondary bg-opacity-20 text-secondary border border-secondary border-opacity-30 font-monospace">12-Week Scan</span>
        </div>
        <div class="sparkline-wrap">
          <svg class="sparkline-svg" viewBox="0 0 260 110">
            <line x1="0" y1="25" x2="260" y2="25" stroke="rgba(255, 255, 255, 0.05)" stroke-width="1" />
            <line x1="0" y1="55" x2="260" y2="55" stroke="rgba(255, 255, 255, 0.05)" stroke-width="1" />
            <line x1="0" y1="85" x2="260" y2="85" stroke="rgba(255, 255, 255, 0.05)" stroke-width="1" />
            <path d="M 10 90 Q 40 85, 60 70 T 110 75 T 150 50 T 190 40 T 230 35 T 250 25 L 250 105 L 10 105 Z" fill="rgba(139, 92, 246, 0.08)" />
            <path d="M 10 90 Q 40 85, 60 70 T 110 75 T 150 50 T 190 40 T 230 35 T 250 25" fill="none" stroke="#8b5cf6" stroke-width="2.5" stroke-linecap="round" stroke-linejoin="round" />
            <circle cx="250" cy="25" r="4" fill="#8b5cf6" />
          </svg>
        </div>
      </div>

    </div>
  </div>

  <!-- Scroll Down Cue (Clean, purposeful) -->
  <a href="#cockpitStart" class="hero-scroll-cue">
    <span>Scroll to Explore</span>
    <i class="bi bi-chevron-down fs-6"></i>
  </a>
</section>'''

html = html.replace(old_hero.replace('\r\n', '\n'), new_hero.replace('\r\n', '\n'))
html = html.replace(old_hero, new_hero)

# 2. Refactor renderToppersCards: Flatten card-inside-card
old_topper_markup = '''        <div class="d-flex justify-content-between align-items-center mb-3 p-2 rounded" style="background: rgba(255, 255, 255, 0.04); border: 1px solid rgba(255, 255, 255, 0.08);">
          <div>
            <span class="small text-muted d-block font-monospace">OVERALL SCORE</span>
            <span class="fs-4 fw-extrabold text-white">${s.composite_score}%</span>
          </div>
          <div class="text-end">
            <span class="small text-muted d-block font-monospace">SGPA RATING</span>
            <span class="badge px-2 py-1 fw-bold fs-6" style="background: rgba(16, 185, 129, 0.2); color: #34d399; border: 1px solid rgba(16, 185, 129, 0.4);">
              ${s.sgpa} / 10.0
            </span>
          </div>
        </div>'''

new_topper_markup = '''        <!-- Flattened Metrics Row (Eliminating nested card-in-card container) -->
        <div class="d-flex justify-content-between align-items-baseline mb-3 pb-3 border-bottom border-secondary border-opacity-10">
          <div>
            <div class="metric-caption">OVERALL SCORE</div>
            <div class="metric-number">${s.composite_score}<span class="metric-unit">%</span></div>
          </div>
          <div class="text-end">
            <div class="metric-caption">SGPA RATING</div>
            <span class="score-pill-neutral">${s.sgpa} / 10.0</span>
          </div>
        </div>'''

html = html.replace(old_topper_markup.replace('\r\n', '\n'), new_topper_markup.replace('\r\n', '\n'))
html = html.replace(old_topper_markup, new_topper_markup)

with open('frontend/templates/dashboard.html', 'w', encoding='utf-8') as f:
    f.write(html)
print('Updated frontend/templates/dashboard.html cleanly.')

