from PIL import Image

# Load the previous frame (last frame where the image is visible)
last_frame = Image.open('/path/to/frame_10.png')

# Get the size of the image
width, height = last_frame.size

# Define the green background color
background_color = (0, 255, 0, 255)  # RGB with full opacity

# Create new frames with the green background
for i in range(1, 4):  # Creating 3 additional frames
    new_frame = Image.new("RGBA", (width, height), background_color)
    new_frame.save(f'frame_10{10+i}.png')