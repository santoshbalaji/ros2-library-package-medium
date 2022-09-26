## Command to build library package
``` colcon build --packages-select try_out_utils ```

## Command to build operational package
``` colcon build --packages-select try_out ```

## Command to test library package
``` colcon test --event-handlers console_direct+ --packages-select try_out_utils ```

## Command to test operational package
``` colcon test --event-handlers console_direct+ --packages-select try_out ```

