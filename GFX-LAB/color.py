x,y,z = input().split()

xx = int(x)
yy = int(y)
zz = int(z)

s= 255


print(xx/s,",",yy/s,",",zz/s)


float backbackwallx = -1.0f, backwally = 0.0f, backwallz = 0.0f;

glm::mat4 backwall_translateMatrix, backwall_rotateXMatrix, backwall_rotateYMatrix, backwall_rotateZMatrix, backwall_scaleMatrix, backwall_fan_scaleMatrix, backwall_model;
backwall_translateMatrix = glm::translate(identityMatrix, glm::vec3(backwallx, backwally - .0025f, backwallz+0.3));
backwall_rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
backwall_rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
backwall_rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
backwall_scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.0f, 0.01f, 6.0f));
backwall_model = backwall_translateMatrix * backwall_rotateXMatrix * backwall_rotateYMatrix * backwall_rotateZMatrix * backwall_scaleMatrix;

ourShader.setMat4("model", backwall_model);

glBindVertexArray(testVBO);
glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

  
backwall_translateMatrix = glm::translate(identityMatrix, glm::vec3(backwallx, backwally + 2.0, backwallz + 0.3));
backwall_model = backwall_translateMatrix * backwall_rotateXMatrix * backwall_rotateYMatrix * backwall_rotateZMatrix * backwall_scaleMatrix;

ourShader.setMat4("model", backwall_model);

glBindVertexArray(testVBO);
glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);