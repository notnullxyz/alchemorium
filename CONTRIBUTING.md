# Contributing to MecGrowMancer
The project can only work if everyone's got the same hardware, connections and code versions. To help this along, it's best to fork and maintain customisations on your fork.
Working together here, heowever, could be majorly beneficial; creating features and customisations on flags that can be turned on or off as needed.

1. Code Style: Follow CPP/Arduino style guide. Use clear, descriptive names. Static Analysis helps.
2. Modularity: Each feature in separate file. Minimize dependencies.
3. Memory: Optimize for ESP32. Avoid dynamic allocation where possible.
4. Documentation: Comment complex logic only. Update README for new features.
5. Add feature flag/configuration for features/hardware not accesible to all.
6. Pull Requests: 
   - One feature/fix per PR
   - Clear description of changes
   - Reference issues if applicable

7. Commit Messages: Concise, descriptive. Start with verb (Add, Fix, Update).
8. License: Ensure contributions comply with GNU GPLv3 License (See COPYING)
9. Hardware Compatibility: Maintain support for ESP32 DOIT DevKit and equivalent
10. Performance: Consider resource/energy constraints. Optimize where necessary.
We appreciate your contributions!
