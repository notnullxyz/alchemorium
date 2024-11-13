# Contributing to Alchemorium

Thank you for your interest in contributing to Alchemorium! Your contributions help us build a robust and versatile project. To ensure a smooth collaboration, please follow the guidelines below.

## General Guidelines

- **Fork the Repository**: To maintain customizations, fork the repository and work on your fork. This ensures that everyone can work with their specific hardware and configurations.
- **Feature Flags**: Implement new features and customizations using feature flags to enable or disable them as needed.

## Code Style

- **Style Guide**: Adhere to the CPP/Arduino style guide.
- **Naming Conventions**: Use clear and descriptive names for variables and functions.
- **Static Analysis**: Utilize static analysis tools to maintain code quality.

## Code Structure

- **Modularity**: Implement each feature in a separate file and minimize dependencies.
- **Memory Management**: Optimize for ESP32, avoiding dynamic allocation when possible.

## Documentation

- **Complex Logic**: Comment only on complex logic to keep the codebase clean.
- **README Updates**: Update the README file to reflect new features.

## Pull Requests

- **Single Purpose**: Each pull request should address one feature or fix.
- **Description**: Provide a clear and concise description of the changes.
- **Issue References**: Reference related issues if applicable.

## Commit Messages

- **Clarity**: Write concise and descriptive commit messages.
- **Format**: Begin with a verb (e.g., Add, Fix, Update).

## Licensing

- **Compliance**: Ensure contributions comply with the GNU GPLv3 License (see COPYING).

## Hardware Compatibility

- **Supported Devices**: Maintain compatibility with ESP32 DOIT DevKit and equivalent hardware.

## Performance Considerations

- **Resource Constraints**: Be mindful of resource and energy constraints and optimize where necessary.

We appreciate your contributions and look forward to working together to enhance Alchemorium!
