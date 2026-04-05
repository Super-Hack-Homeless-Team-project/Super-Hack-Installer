# Super Hack Installer – Changelog

## [1.0.4] – 2026-03-21
### Added
- Settings UI popup allows enabling/disabling:
  - Particle effects
  - Clicking sound
  - Roadmap popup
- Achievement popup when installing the bundle successfully:
  - Basic → "Starter Pack Installed!"
  - VIP → "VIP Installer Master!"
  - Ultimate → "Ultimate Installer Legend!"
- Particle confetti alongside sparkling stars

- Separate background color for each bundle (Basic blue, VIP yellow, Ultimate red)

- Roadmap v1.1 popup displaying upcoming features

### Changed

- Key input popup with bounce and glow effect

- Click sound varies depending on the bundle (click, bell, firework)

- Success alert automatically fades out and scales down after 5 seconds

### Fixed

- CMakeLists.txt updated to avoid duplicate filenames and missing Geode SDK paths
- Build warnings MSB8027 are handled by specifying the source file



## [1.0.3] - 2026-03-19 20h
- fix some bug in 2.2081 in GD
- added 1 key : NeonGD1667


## [1.0.2] - 2026-03-19 
- Added support for multiple license keys (TEST123, VIP456, ULTIMATE789).
- New UI flow: after entering valid key, user can select bundle (Basic / Pro / Ultimate).
- Added simulated installation progress bar for bundle selection.
- General stability improvements and code cleanup.


## [1.0.1] - 2026-03-19
- Removed Vietnamese language (temporary, due to font rendering issues).
- Updated logo for cleaner neon branding.

## [1.0.0] - 2026-03-15
- Initial release of **Super Hack Installer**.
- Added license key and account authentication system.
- Secure server communication for ownership verification.
- Automatic download and installation of **Super Hack Mod Menu** after successful validation.
- Clear feedback messages for success or failure during authentication.
- Lightweight design: acts only as a gateway to protect the main paid mod.
