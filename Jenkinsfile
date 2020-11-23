pipeline {
    agent none

    stages {
        stage('BuildAndTest') {
            matrix {
                axes {
                    axis {
                        name 'PLATFORM'
                        values 'FreeBSD', 'Windows'
                    }
                    axis {
                        name 'COMPILER'
                        values 'g++', 'clang++'
                    }
                }

                agent {
                    label "${PLATFORM}"
                }

                stages {
                    stage('Build Windows') {
                        when {
                            expression { PLATFORM == 'Windows' }
                        }
                        steps {
							dir ('build') {
								sh "rm -rf *"
								sh "cmake -G 'MSYS Makefiles' -DCMAKE_CXX_COMPILER=${COMPILER} .."
								sh "make -j4"
							}
                        }

                    }
                    stage('Build FreeBSD') {
                        when {
                            expression { PLATFORM == 'FreeBSD' }
                        }
                        steps {
							dir ('build') {
								sh "rm -rf *"
								sh "cmake -G 'Unix Makefiles' -DCMAKE_CXX_COMPILER=${COMPILER} .."
								sh "make -j4"
							}
                        }

                    }

                    stage('Test') {
                        steps {
                            echo "Do Test for ${PLATFORM} - ${COMPILER}"
                        }
                    }
                }
            }
        }
    }
}
