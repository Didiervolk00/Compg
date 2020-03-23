from math import *

import numpy as np

from lines import *

# Draw the cube, based on the corners and edges


def printCube(corners, edges):

    # This is based on the edges, not the corners,
    # because corners can have multiple connections
    for i in range(0, len(edges)):

        # Draw a line between the two corners
        canvas.addLine(
            (corners[edges[i][0]].item(0), corners[edges[i][0]].item(1)),
            (corners[edges[i][1]].item(0), corners[edges[i][1]].item(1))
        )

# Transform the cube to an isometric view


def isometric(cornersInput, rotation):

    # We want to work with a local copy of the corners
    cornersInput = cornersInput.copy()

    for i in range(0, len(cornersInput)):

        # The rotation matrix around the y axis
        rotationMatrix = np.matrix(
            [[cos(radians(rotation)), 0, sin(radians(rotation)), 0],
             [0, 1, 0, 0],
             [-sin(radians(rotation)), 0, cos(radians(rotation)), 0],
             [0, 0, 0, 0]]
        )

        # Calculate the vector after the rotation
        cornersInput[i] = np.dot(rotationMatrix, cornersInput[i])

        # The rotation should not affect the last column
        # That's only there for the translation
        cornersInput[i][3] = 1

        # Translate and scale the box
        translateScaleMatrix = np.matrix(
            [[100, 0, 0, 300],
             [0, 100, 0, 150],
             [0, 0, 100, 0],
             [0, 0, 0, 1]]
        )

        # Apply these two transformations
        cornersInput[i] = np.dot(translateScaleMatrix, cornersInput[i])

        # The projection matrix to transform to isometric view
        projectionMatrix = np.matrix(
            [[1/sqrt(2), 0, 1/sqrt(2), 0],
             [1/sqrt(6), sqrt(2/3), (-1)*(1/sqrt(6)), 0]]
        )

        # Apply the isometric view
        cornersInput[i] = np.dot(projectionMatrix, cornersInput[i])

    # Return the new transformed corners
    return cornersInput


# The corners of the cube
# The fourth column is only there for the transformations
corners = [
    np.matrix([[-1], [-1], [-1], [1]]),
    np.matrix([[1], [-1], [-1], [1]]),
    np.matrix([[1], [1], [-1], [1]]),
    np.matrix([[-1], [1], [-1], [1]]),
    np.matrix([[-1], [-1], [1], [1]]),
    np.matrix([[1], [-1], [1], [1]]),
    np.matrix([[1], [1], [1], [1]]),
    np.matrix([[-1], [1], [1], [1]])
]

# All of the connections between the corners
# If you want to see the effect, change a few
edges = (
    (0, 1),
    (1, 2),
    (2, 3),
    (3, 0),
    (0, 4),
    (1, 5),
    (2, 6),
    (3, 7),
    (4, 5),
    (5, 6),
    (6, 7),
    (7, 4),
)

# Create a canvas to draw on
canvas = Lines(640, 480)

# Calculate the corners in isometric view
cornersIsometric = isometric(corners, 30)

# Print the cube on the screen
printCube(cornersIsometric, edges)

# Draw the class
canvas.draw()
